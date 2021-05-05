#pragma once

namespace sir {

  struct ModelConfig {
    double b;
    double c;
    int s;
    int i;
    int r;
  };

class Parser {
  double beta_;
  double gamma_;
  int susceptible_;
  int infected_{1};
  int removed_{0};
  int dayCount_;

public:
  Parser(int argc, char *argv[]);

  [[nodiscard]] double b() const;
  [[nodiscard]] double c() const;
  [[nodiscard]] int s() const;
  [[nodiscard]] int i() const;
  [[nodiscard]] int r() const;
  [[nodiscard]] int dayCount() const;
};

}  // namespace sir
