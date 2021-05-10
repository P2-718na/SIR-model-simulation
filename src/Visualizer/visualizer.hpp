#pragma once
#include <string>

namespace sir {

class Model;

// Class for visualizing data on the terminal.
class Visualizer {
  // Handler to the model used in this visualizer.
  Model& model_;

  // Compute padding required to display numbers correctly up to
  // biggestNumber.
  static int computePadding(int biggestNumber); // Todo this will need a test

  // Return a string with a single character centered in the middle.
  // centerChar is the character to print.
  // width is the total width of the resulting string.
  static std::string center(char centerChar, int width);

  // Return a string with a number aligned to the right.
  static std::string alignRight(int rightNum, int width);

 public:
  explicit Visualizer(Model& model);

  // Display data on a table. Doesn't display anything if dayCount is <= 0.
  // dayCount is the number of days to run the simulation for.
  void displayPretty(int dayCount) const noexcept;

  // Display bare data. (T, S, I, R format). T indicates day number.
  // Doesn't display anything if dayCount is <= 0.
  // dayCount is the number of days to run the simulation for.
  // displayHeadings indicates whether or not the first row should contain
  // headings.
  void display(int dayCount, bool displayHeadings) const noexcept;
};

}
