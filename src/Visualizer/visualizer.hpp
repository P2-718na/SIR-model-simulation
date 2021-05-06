#pragma once
#include <string>

namespace sir {

class Model;

// Class for visualizing data on the terminal.
class Visualizer {
  // Handler to the model used in this visualizer
  Model& model_;

  // Compute padding required to display numbers correctly up to
  // biggestNumber
  static int computePadding(int biggestNumber); // Todo this will need a test

  // Return a string with a single character centered in the middle.
  static std::string center(char centerChar, int width);

  // Return a string with a number aligned to the right.
  static std::string alignRight(int rightNum, int width);

 public:
  explicit Visualizer(Model& model);

  // Display data on a table. Returns false if
  // dayCount is <= 0.
  void displayPretty(int dayCount) const noexcept;

  // Display bare data. (T, S, I, R format). T indicates day
  // number.
  void display(int dayCount, bool displayHeadings) const noexcept;
};

}
