#include <SFML/Graphics.hpp>
#include <iostream>

#include "sir.hpp"

int main() {
  sir::Model model{0.2, 0.1, 1000, 1, 0};
  for (int i = 0; i < 160; i++) {
    model.step();

    std::cout << model.susceptible() << "; " << model.infected() << "; " << model.removed() << ";\n";
  }
}
