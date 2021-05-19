#ifndef PARSER_HPP
#define PARSER_HPP

#include "lyra/lyra.hpp"

namespace sir {

class Parser {
  // Lyra CLI object.
  lyra::cli cli_;

  // Model parameters.
  double beta_{};
  double gamma_{};
  int susceptible_{};
  int infected_{1};
  int removed_{0};
  int dayCount_{};

  // Display type?
  bool prettyPrint_{false};

  // Add column headings? Always true on prettyPrint.
  bool noHeadings_{false};

 public:
  Parser(int argc, char* argv[]);

  // Getter functions.
  double beta() const noexcept;
  double gamma() const noexcept;
  int susceptible() const noexcept;
  int infected() const noexcept;
  int removed() const noexcept;
  int dayCount() const noexcept;
  bool prettyPrint() const noexcept;
  bool displayHeadings() const noexcept;
};

}  // namespace sir

#endif
