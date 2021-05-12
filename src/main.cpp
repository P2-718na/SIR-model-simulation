#include <iostream>

#include "model.hpp"
#include "visualizer.hpp"
#include "parser.hpp"

int main(int argc, char* argv[]) {
  // Catch errors in constructors
  try {
    // Parse CLI Arguments
    sir::Parser parser{argc, argv};

    // Initialise model
    sir::Model model{parser.b(), parser.c(), parser.s(), parser.i(), parser.r()};

    // Initialise visualizer
    sir::Visualizer visualizer{model};

    // If prettyprint is enabled, visualize pretty data and terminate
    // the program.
    if (parser.prettyPrint()) {
      visualizer.displayPretty(parser.dayCount());

      return EXIT_SUCCESS;
    }

    // Otherwise, display normal data and terminate.
    visualizer.display(parser.dayCount(), parser.displayHeadings());

    return EXIT_SUCCESS;
  } catch (const std::range_error &error) {
    std::cerr << "Error: " << error.what() << std::endl;

    return EXIT_FAILURE;
  } catch (...) {
    std::cerr << "Something went horribly wrong. Terminating." << std::endl;

    return EXIT_FAILURE;
  }
}

