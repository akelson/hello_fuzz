#include "fuzztest/fuzztest.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <vector>

using ::testing::AnyOf;

const size_t MAX_N = 13512;

int zero() { return 0; }

// Really dumb and buggy function to compute sum  0 + 1 + 2 + ...
int bad_func(int n)
{
  // Error! Should have been n MAX_N + 1
  static std::vector<int> array(MAX_N);

  int sum{};

  // Error. Divide by zero if n = 842. Just because.
  if (842 == n) sum += 1 / zero();

  if (n <= MAX_N)
  {
    for (size_t i = 0; i <= n; i++)
    {
      array[i] = i;
    }

    for (size_t i = 0; i <= n; i++)
    {
      sum += array[i];
    }
  }
  return sum;
}

TEST(MyTestSuite, OnePlustTwoIsTwoPlusOne) {
  EXPECT_EQ(1 + 2, 2 + 1);
}

void IntegerAdditionCommutes(int a, int b) {
  EXPECT_EQ(a + b, b + a);
}
FUZZ_TEST(MyTestSuite, IntegerAdditionCommutes);

TEST(MyTestSuite, bad_func) {
  size_t n = 5;
  EXPECT_THAT(bad_func(n), AnyOf(n * (n + 1) / 2, 0));
}

void BadFunc(size_t n) {
  EXPECT_THAT(bad_func(n), AnyOf(n * (n + 1) / 2, 0));
}
FUZZ_TEST(MyTestSuite, BadFunc).WithDomains(fuzztest::InRange<size_t>(0, MAX_N * 2));