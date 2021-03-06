#include <iostream>
#include <string>

#include "visualizer.hpp"
#include "model.hpp"

// Added to remove unnecessary characters in cout statements.
using std::endl;

namespace sir {

Visualizer::Visualizer(Model& model) : model_{model} {}

int Visualizer::computePadding(int biggestNumber) {
  int padding = 0;
  while ((biggestNumber /= 10) != 0) {
    ++padding;
  }

  return padding + 1;
}

std::string Visualizer::center(char centerChar, int width) {
  std::string spaces(width / 2, ' ');

  // If width is even, we need to return one less character
  if (width % 2 == 0) {
    return spaces + centerChar + spaces.substr(0, spaces.length() - 1);
  }

  // If width is odd, no calculation is needed. (One character gets truncated
  // by integer division).
  return spaces + centerChar + spaces;
}

std::string Visualizer::alignRight(int rightNum, int width) {
  std::string spaces(width - computePadding(rightNum), ' ');
  return spaces + std::to_string(rightNum);
}

void Visualizer::displayPretty(int dayCount) const noexcept {
  // We need at least one day to print some data.
  if (dayCount <= 0) {
    return;
  }

  // Compute padding required to display data. Add +1 for readability.
  const int padding =
    computePadding(dayCount > model_.total() ? dayCount : model_.total()) + 1;

  // Box characters used
  //    ┌─┬─┐
  //   │ │ │
  //  ├─┼─┤
  // └─┴─┘

  std::string row(padding, '-');

  // Print first line of table header.
  std::cout << "┌" << row << "┬" << row << "┬" << row << "┬" << row << "┐"
            << endl;

  // Print T, S, I, R, centered.
  std::cout << "│" << center('T', padding) << "│" << center('S', padding) << "│"
            << center('I', padding) << "│" << center('R', padding) << "│"
            << endl;

  // Print table body.
  // Note that the number of values printed is dayCount + 1, since the
  // initial state is printed as well.
  for (int day = 0; day != dayCount + 1; ++day) {
    // Print table line.
    std::cout << "├" << row << "┼" << row << "┼" << row << "┼" << row << "┤"
              << endl;

    // Print state values.
    std::cout << "│" << alignRight(day + 1, padding) << "|"
              << alignRight(model_.susceptible(), padding) << "│"
              << alignRight(model_.infected(), padding) << "│"
              << alignRight(model_.removed(), padding) << "│" << endl;

    // Simulate one day.
    model_.step();
  }

  // Print last line of table.
  std::cout << "└" << row << "┴" << row << "┴" << row << "┴" << row << "┘"
            << endl;
}

void Visualizer::display(int dayCount, bool displayHeadings) const noexcept {
  if (dayCount <= 0) {
    return;
  }

  // Print headings if asked by the user
  if (displayHeadings) {
    std::cout << "Current_day"
              << " "
              << "Susceptible"
              << " "
              << "Infected"
              << " "
              << "Removed" << endl;
  }

  // Print data.
  // Note that the number of values printed is dayCount + 1, since the
  // initial state is printed as well.
  for (int day = 0; day != dayCount + 1; ++day) {
    // Print state values.
    std::cout << day << " " << model_.susceptible() << " " << model_.infected()
              << " " << model_.removed() << endl;

    // Simulate one day.
    model_.step();
  }
}

}  // namespace sir
