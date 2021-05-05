#include <iostream>
#include <stdexcept>

#include "lyra/lyra.hpp"
#include "parser.hpp"

namespace sir {

  Parser::Parser(int argc, char **argv) {
    bool showHelp = false;

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
          ("Duration of the simulation.").required();

    auto result = cli_.parse({argc, argv});

    if (!result) {
      std::cerr
        << "Error in command line: "
        << result.errorMessage()
        << std::endl
        << cli_;

      exit(1);
    }

    if (showHelp) {
      std::cout << cli_;

      exit(1);
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

}
