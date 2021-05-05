#include <iostream>
#include <stdexcept>

#include "lyra/lyra.hpp"
#include "parser.hpp"

namespace sir {

Parser::Parser(int argc, char **argv) {
  auto cli = lyra::cli()
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
             ["-i"]["--infected"]
                ("Number of removed people. Defaults to 0.")
             | lyra::opt(dayCount_, "dayCount")
             ["-t"]["--day-count"]
                ("Duration of the simulation.").required();

  auto result = cli.parse({argc, argv});

  if (!result) {
    throw std::runtime_error(result.errorMessage());
  }
}

  double Parser::b() const {
    return beta_;
  }

  double Parser::c() const {
    return gamma_;
  }

  int Parser::s() const {
    return susceptible_;
  }

  int Parser::i() const {
    return infected_;
  }

  int Parser::r() const {
    return removed_;
  }

  int Parser::dayCount() const {
    return dayCount_;
  }

}
