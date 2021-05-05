#pragma once

#include "lyra/lyra.hpp"

namespace sir {

class Parser {
  lyra::cli cli_;

  // Model parameters.
  double beta_;
  double gamma_;
  int susceptible_;
  int infected_{1};
  int removed_{0};

  // Other parameters.
  int dayCount_;

  // Display type?
  bool prettyPrint_{false};

public:
  Parser(int argc, char *argv[]);

  // Getter functions.
  double b() const noexcept;
  double c() const noexcept;
  int s() const noexcept;
  int i() const noexcept;
  int r() const noexcept;
  int dayCount() const noexcept;
  int prettyPrint() const noexcept;
};

}  // namespace sir
