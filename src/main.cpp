#include <SFML/Graphics.hpp>
#include <iostream>

#include "model.hpp"
#include "visualizer.hpp"

int main() {
  sir::Model model{0.2, 0.1, 1000, 1, 0};

  sir::TUIVisualizer visualizer{&model};

  visualizer.display(160);
}
