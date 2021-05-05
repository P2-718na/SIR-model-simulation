#pragma once

namespace sir {

// Struct containing a single state (number of susceptible, infected
// and removed people).
struct State {
  int s;
  int i;
  int r;
};

class Model {
  // Beta parameter for the simulation. Represents infection probability.
  // Must be a value in range [0, 1].
  // Defined at the beginning of the simulation.
  // Can be altered by external factors.
  double b_;

  // Gamma parameter for the simulation. Represents chance of healing.
  // Must be a value in range [0, 1].
  // Defined at the beginning of the simulation.
  // Can be altered by external factors.
  double c_;

  // Represents people who might get infected.
  // Fixed at the beginning of the simulation.
  double s_;

  // Represents people who are infected and can infect others.
  // Fixed at the beginning of the simulation.
  double i_;

  // Represents dead, healed or quarantined people.
  // Fixed at the beginning of the simulation.
  double r_;

  // Total count (s_ + i_ + r_)
  // Computed at the beginning of the simulation.
  int n_;

 public:
  // Constructors //////////////////////////////////////////////////////////////
  Model(double beta, double gamma, int susceptible, int infected, int removed);

  // Accessors /////////////////////////////////////////////////////////////////
  // Getter function for beta.
  const double& beta() const noexcept;
  // Setter function for beta. If newBeta is not in range, returns false
  // and leaves beta unchanged.
  bool beta(double newBeta) noexcept;

  // Getter function for gamma.
  // TODO ask const double& vs double const&
  const double& gamma() const noexcept;
  // Setter function for gamma. if newGamma is not in range, returns false
  // and leaves gamma unchanged.
  bool gamma(double newGamma) noexcept;

  // Getter function for susceptible count.
  int susceptible() const noexcept;

  // Getter function for infected count.
  int infected() const noexcept;

  // Getter function for removed count.
  int removed() const noexcept;

  // Getter function for whole state (s, i, r).
  State state() const noexcept;

  // Methods ///////////////////////////////////////////////////////////////////
  // Simulate one day.
  void step() noexcept;
};
}