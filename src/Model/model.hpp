#ifndef MODEL_HPP
#define MODEL_HPP

namespace sir {

class Model {
  // Beta parameter for the simulation. Represents infection probability.
  // Must be a value in range [0, 1].
  // Must be initialized in constructor
  // Can be altered using beta(double newBeta) setter
  double b_;

  // Gamma parameter for the simulation. Represents chance of healing.
  // Must be a value in range [0, 1].
  // Must be initialized in constructor
  // Can be altered using gamma(double newGamma) setter
  double c_;

  // Represents people who might get infected.
  // Must be initialized in constructor, cannot be changed.
  // Must be a number greater than 0 and lesser than 500 million.
  double s_;

  // Represents people who are infected and can infect others.
  // Must be initialized in constructor, cannot be changed.
  // Must be a number greater than 0 and lesser than 500 million.
  double i_;

  // Represents dead, healed or quarantined people.
  // Must be initialized in constructor, cannot be changed.
  // Must be a number greater than 0 and lesser than 500 million.
  double r_;

  // Total count (s_ + i_ + r_)
  // Computed at the beginning of the simulation.
  int n_;

 public:
  // Constructors //////////////////////////////////////////////////////////////
  Model(double beta, double gamma, int susceptible, int infected, int removed);

  // Accessors /////////////////////////////////////////////////////////////////
  // Getter function for beta.
  [[nodiscard]] double beta() const noexcept;
  // Setter function for beta. If newBeta is not in range, returns false
  // and leaves beta unchanged.
  [[nodiscard]] bool beta(double newBeta) noexcept;

  // Getter function for gamma.
  [[nodiscard]] double gamma() const noexcept;
  // Setter function for gamma. if newGamma is not in range, returns false
  // and leaves gamma unchanged.
  [[nodiscard]] bool gamma(double newGamma) noexcept;

  // Getter function for susceptible count (s_).
  // The number of susceptible people is rounded down to the nearest integer.
  [[nodiscard]] int susceptible() const noexcept;

  // Getter function for infected count (i_).
  // The number of infected people is rounded down to the nearest integer.
  [[nodiscard]] int infected() const noexcept;

  // Getter function for removed count (r_).
  // The number of removed people is rounded down to the nearest integer.
  [[nodiscard]] int removed() const noexcept;

  // Getter function for total population count (n_).
  [[nodiscard]] int total() const noexcept;

  // Methods ///////////////////////////////////////////////////////////////////
  // Step the simulation forward one day.
  void step() noexcept;
};

}  // namespace sir

#endif
