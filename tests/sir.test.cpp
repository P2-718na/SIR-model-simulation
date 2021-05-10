// Doctest requires this define to be specified only once.
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <random>

#include "doctest.h"
#include "model.hpp"

TEST_CASE("SIR Model constructor parameters checks") {
  // todo replace this with smart pointers once they are taught in lesson
  // since no delete is called (for now)
  sir::Model* model;

  // We use require in the first two subcases, since the rest of
  // the implementation strictly relies on these assertions.
  SUBCASE("Valori corretti 1") {
    const double b = 0;
    const double c = 1;

    const int s = 1;
    const int i = 2;
    const int r = 3;

    REQUIRE_NOTHROW(model = new sir::Model{b, c, s, i, r});

    REQUIRE_EQ(model->beta(), b);
    REQUIRE_EQ(model->gamma(), c);
    REQUIRE_EQ(model->susceptible(), s);
    REQUIRE_EQ(model->infected(), i);
    REQUIRE_EQ(model->removed(), r);

    REQUIRE_EQ(model->total(), s + i + r);
  }

  SUBCASE("Valori corretti 2") {
    const double b = 0.2;
    const double c = 0.8;

    const int s = 5;
    const int i = 9;
    const int r = 14;

    REQUIRE_NOTHROW(model = new sir::Model{b, c, s, i, r});

    REQUIRE_EQ(model->beta(), b);
    REQUIRE_EQ(model->gamma(), c);
    REQUIRE_EQ(model->susceptible(), s);
    REQUIRE_EQ(model->infected(), i);
    REQUIRE_EQ(model->removed(), r);

    REQUIRE_EQ(model->total(), s + i + r);
  }

  SUBCASE("Valori incorretti") {
    // We use check instead of require here, because
    // the rest of the implementation does not strictly rely on this.
    CHECK_THROWS(model = new sir::Model{-1, 1, 1, 2, 3});

    CHECK_THROWS(model = new sir::Model{1, 2, 1, 2, 3});

    CHECK_THROWS(model = new sir::Model{0.5, 1, -1, -2, 3});

    CHECK_THROWS(model = new sir::Model{0.5, 1, 0, 0, 0});
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
std::uniform_int_distribution<int> greaterThanZero(1, +2147483647);
std::uniform_int_distribution<int> stepCount(1, 1000000);

struct

TEST_CASE("SIR Model with random values") {
  // Repeat test multiple times with random values
  for (int test = 0; test < 50; ++test) {
    const double b = betaGamma(generator);
    const double c = betaGamma(generator);

    const int s = greaterThanZero(generator);
    const int i = greaterThanZero(generator);
    const int r = greaterThanZero(generator);

    std::stringstream subcaseName;

    subcaseName << "Random test with values:" << b << ", " << c << ", "
                << s << ", " << i << ", " << r << std::endl;

    SUBCASE(subcaseName.str()) {
      sir::Model model = sir::Model{b, c, s, i, r};

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

        // todo test, gamma inverse mean time of infection resolution
        if (model.infected() <= 1) {
          CHECK_EQ(
            model.gamma(),
            doctest::Approx(1.f / static_cast<float>(step)).epsilon(0.1));

          break;
        }
      }
    }
  }
}

