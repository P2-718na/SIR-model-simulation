#include <stdexcept>

#include "sir.hpp"

// Constructor /////////////////////////////////////////////////////////////////
Model::Model(
  double beta,
  double gamma,
  int susceptible,
  int infected,
  int removed
) {
  // Check values for beta and gamma parameters.
  if (!this->beta(beta)) {
    throw std::range_error(
      "beta parameter is not in range."
    );
  }

  if (!this->gamma(gamma)) {
    throw std::range_error(
       "gamma parameter is not in range."
    );
  }

  // Check values for s, i, r parameters.
  if (susceptible < 0) {
    throw std::range_error(
       "susceptible parameter must be positive."
    );
  }
  s_ = susceptible;

  if (infected < 0) {
    throw std::range_error(
       "infected parameter must be positive."
    );
  }
  i_ = infected;

  if (removed < 0) {
    throw std::range_error(
       "removed parameter must be positive."
    );
  }
  r_ = removed;

  // Check that there is at least one person in the simulation.
  n_ = s_ + i_ + r_;
  if (n_ == 0) {
    throw std::range_error(
       "There mus be at least one person in the simulation."
    );
  }

}

// Accessors ///////////////////////////////////////////////////////////////////
const double &Model::beta() const noexcept {
  return b_;
}

bool Model::beta(double newBeta) noexcept {
  if (newBeta > 1 || newBeta < 0) {
    return false;
  }

  b_ = newBeta;
  return true;
}

const double &Model::gamma() const noexcept {
  return c_;
}

bool Model::gamma(double newGamma) noexcept {
  if (newGamma > 1 || newGamma < 0) {
    return false;
  }

  c_ = newGamma;
  return true;
}

const int &Model::susceptible() const noexcept {
  return s_;
}

const int &Model::infected() const noexcept {
  return i_;
}

const int &Model::removed() const noexcept {
  return r_;
}

