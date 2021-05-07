#include <iostream>
#include <stdexcept>

#include "lyra/lyra.hpp"
#include "parser.hpp"

namespace sir {

Parser::Parser(int argc, char **argv) {
  bool showHelp = false;

  // todo add checks
  // Generate parser object. (Note that this mus be done inside here, since
  // it needs to know where to store values.
  cli_ |=
     lyra::help(showHelp)
     | lyra::opt(beta_, "beta")
     ["-b"]["--beta"]
        ("Beta constant. Must be a number in range [0, 1].").required()
     | lyra::opt(gamma_, "gamma")
     ["-c"]["--gamma"]
        ("Gamma constant. Must be a number in range [0, 1].").required()
     | lyra::opt(susceptible_, "susceptible")
     ["-s"]["--susceptible"]
        ("Number of susceptible people.").required()
     | lyra::opt(infected_, "infected")
     ["-i"]["--infected"]
        ("Number of infected people. Defaults to 1.")
     | lyra::opt(removed_, "removed")
     ["-r"]["--removed"]
        ("Number of removed people. Defaults to 0.")
     | lyra::opt(dayCount_, "dayCount")
     ["-t"]["--day-count"]
        ("Duration of the simulation.").required()
    | lyra::opt(prettyPrint_)
    ["--pretty"]
       ("Prints a pretty table to the terminal.")
    | lyra::opt(noHeadings_)
    ["--no-headings"]
       ("Remove headings from normal print. "
        "Ignored if --pretty is added as well.");


  // If no arguments were specified, display help and terminate the program.
  if (argc == 1) {
    std::cout << cli_;

    exit(1);
  }

  // If there are arguments, parse them.
  auto result = cli_.parse({argc, argv});

  // If there was an error parsing arguments, inform the user and terminate
  // the program.
  if (!result) {
    std::cerr
      << "Error in command line: "
      << result.errorMessage()
      << std::endl;

    exit(1);
  }

  // Display help and terminate the program if the user asked for it.
  if (showHelp) {
    std::cout << cli_;

    exit(0);
  }
}

double Parser::b() const noexcept {
  return beta_;
}

double Parser::c() const noexcept {
  return gamma_;
}

int Parser::s() const noexcept {
  return susceptible_;
}

int Parser::i() const noexcept {
  return infected_;
}

int Parser::r() const noexcept {
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

}
