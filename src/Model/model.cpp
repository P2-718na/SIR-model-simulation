#include "model.hpp"

#include <cmath>  //todo ask if correct
#include <stdexcept>

namespace sir {
// Constructors ////////////////////////////////////////////////////////////////
Model::Model(
  double beta, double gamma, int susceptible, int infected, int removed) {
  // Check values for beta and gamma parameters.
  if (!this->beta(beta)) {
    throw std::range_error("beta parameter is not in range.");
  }

  if (!this->gamma(gamma)) {
    throw std::range_error("gamma parameter is not in range.");
  }

  // Check values for s, i, r parameters.
  if (susceptible < 0) {
    throw std::range_error("susceptible parameter must be positive.");
  }
  s_ = susceptible;

  if (infected < 0) {
    throw std::range_error("infected parameter must be positive.");
  }
  i_ = infected;

  if (removed < 0) {
    throw std::range_error("removed parameter must be positive.");
  }
  r_ = removed;

  // Check that there is at least one person in the simulation.
  n_ = s_ + i_ + r_;
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
  // s_ -= bsni; Don't update S just yet...
  i_ += bsni - ci;
  r_ += ci;

  // Since s + i + r is constant, update S based on that. This also accounts
  // for floating point and rounding errors.
  // S cannot be negative, since infected and removed are rounded down.
  s_ = n_ - this->infected() - this->removed();
}
}
