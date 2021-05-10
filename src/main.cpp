#include <iostream>

#include "model.hpp"
#include "visualizer.hpp"
#include "parser.hpp"

int main(int argc, char* argv[]) {
  //todo w8 for smart pointers
  try {
    // Parse CLI Arguments
    sir::Parser parser{argc, argv};

    // Initialise model
    sir::Model model{parser.b(), parser.c(), parser.s(), parser.i(), parser.r()};

    // Initialise visualizer
    sir::Visualizer visualizer{model};

    // Visualize data
    if (parser.prettyPrint()) {
      visualizer.displayPretty(parser.dayCount());
    } else {
      visualizer.display(parser.dayCount(), parser.displayHeadings());
    }
  } catch (const std::range_error &error) {
    std::cerr << "Error: " << error.what() << std::endl;

    return 1;
  } catch (...) {
    std::cerr << "Something went horribly wrong. Terminating." << std::endl;

    return 1;
  }

  // Return
  return 0;
}

