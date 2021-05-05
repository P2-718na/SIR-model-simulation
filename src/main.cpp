#include <iostream>

#include "model.hpp"
#include "visualizer.hpp"
#include "parser.hpp"

int main(int argc, char* argv[]) {
  // Parse CLI Arguments
  // Todo show help if no arguments
  sir::Parser parser(argc, argv);

  sir::Model model{parser.b(), parser.c(), parser.s(), parser.i(), parser.r()};

  sir::TUIVisualizer visualizer{model};

  if (parser.prettyPrint()) {
     visualizer.displayPretty(parser.dayCount());
  } else {
    visualizer.display(parser.dayCount());
  }
}

