// Doctest requires this define to be specified only once.
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <random>

#include "doctest.h"
#include "model.hpp"

// These are not const because it is required by a test.
struct TestData {
  double b{};
  double c{};
  int s{};
  int i{};
  int r{};
};

std::ostream& operator<< (std::ostream& os, const TestData& value) {
  os << "b: " << value.b << ", c: " << value.c << ", s: " << value.s
     << ", i: " << value.i << ", r: " << value.r;
  return os;
}

TEST_CASE("SIR Model constructor parameters checks") {
  // todo replace this with smart pointers once they are taught in lesson
  // since no delete is called (for now)
  sir::Model* model;

  // We use require in the first two subcases, since the rest of
  // the implementation strictly relies on these assertions.
  SUBCASE("Valori corretti 1") {
    TestData td{0, 1, 1, 2, 3};

    REQUIRE_NOTHROW(model = new sir::Model{td.b, td.c, td.s, td.i, td.r});

    REQUIRE_EQ(model->beta(), td.b);
    REQUIRE_EQ(model->gamma(), td.c);
    REQUIRE_EQ(model->susceptible(), td.s);
    REQUIRE_EQ(model->infected(), td.i);
    REQUIRE_EQ(model->removed(), td.r);

    REQUIRE_EQ(model->total(), td.s + td.i + td.r);
  }

  SUBCASE("Valori corretti 2") {
    TestData td{0.2, 0.8, 5, 9, 14};

    REQUIRE_NOTHROW(model = new sir::Model{td.b, td.c, td.s, td.i, td.r});

    REQUIRE_EQ(model->beta(), td.b);
    REQUIRE_EQ(model->gamma(), td.c);
    REQUIRE_EQ(model->susceptible(), td.s);
    REQUIRE_EQ(model->infected(), td.i);
    REQUIRE_EQ(model->removed(), td.r);

    REQUIRE_EQ(model->total(), td.s + td.i + td.r);
  }

  SUBCASE("Valori incorretti") {
    // We use check instead of require here, because
    // the rest of the implementation does not strictly rely on this.
    CHECK_THROWS(model = new sir::Model{-1, 1, 1, 2, 3});

    CHECK_THROWS(model = new sir::Model{1, 2, 1, 2, 3});

    CHECK_THROWS(model = new sir::Model{0.5, 1, -1, -2, 3});

    CHECK_THROWS(model = new sir::Model{0.5, 1, 0, 0, 0});

    CHECK_THROWS(model = new sir::Model{0.5, 1, 0, 0, 5000000});
  }
}

//TODO ask if this should be here vv

// Initialize random number generator.
// random_device (slower) calls OS to generate a seed for mt19937 generator
// (faster).
std::random_device rd;
std::mt19937 generator{rd()};

// uniform_real_distribution generates values in [a, b[ instead of
// [a, b]. This is irrelevant, since the chances of landing exactly on
// b for double types is very small.
std::uniform_real_distribution<double> betaGamma(0, 1);
std::uniform_int_distribution<int> greaterThanZero(1, 5E6);
std::uniform_int_distribution<int> stepCount(1, 1E6);

TEST_CASE("SIR Model with random values") {
  // Repeat test multiple times with random values
  TestData td;

  // fixme might be worth asking
  // no real way to do cases with parametrized data.
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

  REQUIRE(td.s + td.i + td.r > 0) ;

  sir::Model model = sir::Model{td.b, td.c, td.s, td.i, td.r};

  REQUIRE_EQ(model.total(), td.s + td.i + td.r);

  // can't use greaterThanZero here, it's too large.
  const int steps = stepCount(generator);
  for (int step = 0; step < steps; ++step) {
    model.step();

    CHECK_EQ(
      model.susceptible() + model.infected() + model.removed(),
      model.total());

    CHECK(model.susceptible() >= 0);
    CHECK(model.infected() >= 0);
    CHECK(model.removed() >= 0);
  }
}

