#pragma once

#include "lyra/lyra.hpp"

namespace sir {

  struct ModelConfig {
    double b;
    double c;
    int s;
    int i;
    int r;
  };

class Parser {
  lyra::cli cli_;

  double beta_;
  double gamma_;
  int susceptible_;
  int infected_{1};
  int removed_{0};
  int dayCount_;

public:
  Parser(int argc, char *argv[]);

  double b() const noexcept;
  double c() const noexcept;
  int s() const noexcept;
  int i() const noexcept;
  int r() const noexcept;
  int dayCount() const noexcept;
};

}  // namespace sir
