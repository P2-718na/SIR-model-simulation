#include <stdexcept>

#include "model.hpp"

namespace sir {

// Constructors ////////////////////////////////////////////////////////////////
Model::Model(
  double beta, double gamma, int susceptible, int infected, int removed) {
  // Check values for beta and gamma parameters.
  // this-> is required here
  if (!this->beta(beta)) {
    throw std::range_error("beta parameter out of range.");
  }

  // this-> is required here
  if (!this->gamma(gamma)) {
    throw std::range_error("gamma parameter out of range.");
  }

  // Check values for s, i, r parameters.
  // The upper limit of 5E6 is arbitrary. It was added to prevent overflow
  // errors.
  if (susceptible < 0 || susceptible >= 5E6) {
    throw std::range_error("susceptible parameter out of range.");
  }
  s_ = susceptible;

  if (infected < 0 || infected >= 5E6) {
    throw std::range_error("infected parameter out of range.");
  }
  i_ = infected;

  if (removed < 0 || removed >= 5E6) {
    throw std::range_error("removed parameter out of range.");
  }
  r_ = removed;

  // Check that there is at least one person in the simulation.
  // N can't be <0, since s_, i_ and r_ are all greater or equal to zero.
  // this-> is required here.
  n_ = this->susceptible() + this->infected() + this->removed();
  if (n_ == 0) {
    throw std::range_error("There must be at least one person.");
  }
}

// Accessors ///////////////////////////////////////////////////////////////////
double Model::beta() const noexcept {
  return b_;
}

bool Model::beta(double newBeta) noexcept {
  if (newBeta > 1 || newBeta < 0) {
    return false;
  }

  b_ = newBeta;
  return true;
}

double Model::gamma() const noexcept {
  return c_;
}

bool Model::gamma(double newGamma) noexcept {
  if (newGamma > 1 || newGamma < 0) {
    return false;
  }

  c_ = newGamma;
  return true;
}

int Model::susceptible() const noexcept {
  return static_cast<int>(s_);
}

int Model::infected() const noexcept {
  return static_cast<int>(i_);
}

int Model::removed() const noexcept {
  return static_cast<int>(r_);
}

int Model::total() const noexcept {
  return n_;
};

// Methods /////////////////////////////////////////////////////////////////////
void Model::step() noexcept {
  // I * beta * S / N.
  const double bsni = b_ * s_ / n_ * i_;

  // gamma * I. Used multiple times in calculations.
  const double ci = c_ * i_;

  // Update values
  s_ -= bsni;
  i_ += bsni - ci;
  // r_ += ci; Don't update R just yet...

  // Since s + i + r is constant, update R based on that. This also accounts
  // for floating point and rounding errors.
  // R cannot be negative, since susceptible and infected are rounded down.
  r_ = n_ - susceptible() - infected();
}

}  // namespace sir
