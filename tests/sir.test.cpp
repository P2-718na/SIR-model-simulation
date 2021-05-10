// Doctest requires this define to be specified only once.
// Probably this is the best place
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

TEST_CASE("SIR test") {
  CHECK(true);
}

// todo test that s + i  + r = constant
// todo test, gamma inverse mean time of infection resolution
// todo test s, i, r always positive
