// Doctest requires this define to be specified only once.
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <random>

#include "doctest.h"
#include "model.hpp"

// Initialize random number generator.
// mt19937 was not used since it is slower and it's not critical for tests.
// We want our tests to be deterministic, seed is a fixed value..
std::default_random_engine generator{42};

// uniform_real_distribution generates values in [a, b[ instead of
// [a, b]. This is irrelevant, since the chances of landing exactly on
// b for double types is very small.
std::uniform_real_distribution<double> betaGamma(0, 1);
std::uniform_int_distribution<int> greaterThanZero(1, 5E6);
std::uniform_int_distribution<int> stepCount(1, 1E6);

// This is necessary to parametrize tests.
struct TestData {
  double b{};
  double c{};
  int s{};
  int i{};
  int r{};
};

// Overload function used by doctest CAPTURE function.
std::ostream& operator<<(std::ostream& os, const TestData& value) {
  os << "b: " << value.b << ", c: " << value.c << ", s: " << value.s
     << ", i: " << value.i << ", r: " << value.r;
  return os;
}

TEST_CASE("Model class constructor works correctly.") {
  sir::Model* model;
  TestData td;

  SUBCASE("Valori corretti 1") {
    td = TestData{0, 1, 1, 2, 3};
  }
  SUBCASE("Valori corretti 2") {
    td = TestData{0.2, 0.8, 5, 9, 14};
  }

  CAPTURE(td);

  REQUIRE_NOTHROW(model = new sir::Model{td.b, td.c, td.s, td.i, td.r});

  REQUIRE_EQ(model->beta(), td.b);
  REQUIRE_EQ(model->gamma(), td.c);
  REQUIRE_EQ(model->susceptible(), td.s);
  REQUIRE_EQ(model->infected(), td.i);
  REQUIRE_EQ(model->removed(), td.r);

  REQUIRE_EQ(model->total(), td.s + td.i + td.r);

  delete model;
}

TEST_CASE("Model class constructor throws for incorrect values.") {
  TestData td;

  SUBCASE("Valori incorretti 1") {
    td = TestData{-1, 1, 1, 2, 3};
  }
  SUBCASE("Valori incorretti 1") {
    td = TestData{1, 2, 1, 2, 3};
  }
  SUBCASE("Valori incorretti 1") {
    td = TestData{0.5, 1, -1, -2, 3};
  }
  SUBCASE("Valori incorretti 1") {
    td = TestData{0.5, 1, 0, 0, 0};
  }
  SUBCASE("Valori incorretti 1") {
    td = TestData{0.5, 1, 0, 0, 5000000};
  }

  CAPTURE(td);

  CHECK_THROWS(sir::Model{td.b, td.c, td.s, td.i, td.r});
}

TEST_CASE("Model test with random values") {
  TestData td;

  // There is no real way to do parametrized test with an arbitrary number
  // of randomly generated parameters.
  SUBCASE("") {
    td = {betaGamma(generator), betaGamma(generator),
      greaterThanZero(generator), greaterThanZero(generator),
      greaterThanZero(generator)};
  }
  SUBCASE("") {
    td = {betaGamma(generator), betaGamma(generator),
      greaterThanZero(generator), greaterThanZero(generator),
      greaterThanZero(generator)};
  }
  SUBCASE("") {
    td = {betaGamma(generator), betaGamma(generator),
      greaterThanZero(generator), greaterThanZero(generator),
      greaterThanZero(generator)};
  }
  SUBCASE("") {
    td = {betaGamma(generator), betaGamma(generator),
      greaterThanZero(generator), greaterThanZero(generator),
      greaterThanZero(generator)};
  }
  SUBCASE("") {
    td = {betaGamma(generator), betaGamma(generator),
      greaterThanZero(generator), greaterThanZero(generator),
      greaterThanZero(generator)};
  }

  CAPTURE(td);

  REQUIRE(td.s + td.i + td.r > 0);

  sir::Model model = sir::Model{td.b, td.c, td.s, td.i, td.r};

  REQUIRE_EQ(model.total(), td.s + td.i + td.r);

  // Step forward and check that the constraints are met.
  const int steps = stepCount(generator);
  for (int step = 0; step < steps; ++step) {
    model.step();

    CHECK_EQ(
      model.susceptible() + model.infected() + model.removed(), model.total());

    CHECK(model.susceptible() >= 0);
    CHECK(model.infected() >= 0);
    CHECK(model.removed() >= 0);
  }
}
