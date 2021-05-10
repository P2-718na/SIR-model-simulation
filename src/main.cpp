#include <iostream>

#include "model.hpp"
#include "visualizer.hpp"
#include "parser.hpp"

int main(int argc, char* argv[]) {
  // Parse CLI Arguments
  sir::Parser parser(argc, argv);

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

  // Return
  return 0;
}

