#pragma once
#include <string>

namespace sir {

class Model;

// Class for handling generation of data used by TUIVisualizer and
// GUIVisualizer
class Visualizer {
 protected:
  // Handler to the model used in this visualizer
  Model* model_;

 public:
  explicit Visualizer(Model* model);
};

// Class for visualizing data on the terminal.
// Data will be printed as a table
class TUIVisualizer : Visualizer {
  // Compute padding required to display numbers correctly up to
  // biggestNumber
  static int computePadding(int biggestNumber); // Todo this will need a test

  // Return a string with a single character centered in the middle.
  static std::string center(char centerChar, int width);

  // Return a string with a number aligned to the right.
  static std::string alignRight(int rightNum, int width);

 public:
  explicit TUIVisualizer(Model* model);

  // Display data on a table. Returns false if
  // dayCount is <= 0.
  bool display(int dayCount) const noexcept;
};

class GUIVisualizer : Visualizer {

};

}