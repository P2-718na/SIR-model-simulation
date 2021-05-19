#include <iostream>
#include <stdexcept>

#include "parser.hpp"
#include "lyra/lyra.hpp"

namespace sir {

Parser::Parser(int argc, char** argv) {
  bool showHelp = false;

  // Generate parser object. (Note that this must be declared inside here, it
  // cannot be a static object).
  /* clang-format off */
  cli_ |=
     lyra::help(showHelp)
     | lyra::opt(beta_, "beta")
     ["-b"]["--beta"]
       ("Beta constant. Must be a number in range [0, 1].")
       .required()
     | lyra::opt(gamma_, "gamma")
     ["-c"]["-g"]["--gamma"]
       ("Gamma constant. Must be a number in range [0, 1].")
       .required()
     | lyra::opt(susceptible_, "susceptible")
     ["-s"]["--susceptible"]
       ("Number of susceptible people.")
       .required()
     | lyra::opt(infected_, "infected")
     ["-i"]["--infected"]
       ("Number of infected people. Defaults to 1.")
     | lyra::opt(removed_, "removed")
     ["-r"]["--removed"]
       ("Number of removed people. Defaults to 0.")
     | lyra::opt(dayCount_, "dayCount")
     ["-t"]["--day-count"]
       ("Duration of the simulation.")
       .required()
       .choices([](int val) { return val >= 0; })
    | lyra::opt(prettyPrint_)
    ["--pretty"]
      ("Prints a pretty table to the terminal.")
    | lyra::opt(noHeadings_)
    ["--no-headings"]
      ("Remove headings from normal print. "
       "Ignored if --pretty is added as well.");
  /* clang-format on */

  // If no arguments were specified, display help and terminate the program.
  if (argc == 1) {
    std::cout << cli_;
    exit(EXIT_FAILURE);
  }

  // If there are arguments, parse them.
  auto result = cli_.parse({argc, argv});

  // If there was an error parsing arguments, inform the user and terminate
  // the program.
  if (!result) {
    std::cerr << "Error in command line: " << result.errorMessage()
              << std::endl;
    exit(EXIT_FAILURE);
  }

  // Display help and terminate the program if the user asked for it.
  if (showHelp) {
    std::cout << cli_;
    exit(EXIT_SUCCESS);
  }
}

double Parser::beta() const noexcept {
  return beta_;
}

double Parser::gamma() const noexcept {
  return gamma_;
}

int Parser::susceptible() const noexcept {
  return susceptible_;
}

int Parser::infected() const noexcept {
  return infected_;
}

int Parser::removed() const noexcept {
  return removed_;
}

int Parser::dayCount() const noexcept {
  return dayCount_;
}

bool Parser::prettyPrint() const noexcept {
  return prettyPrint_;
}

bool Parser::displayHeadings() const noexcept {
  return !noHeadings_;
}

}  // namespace sir
