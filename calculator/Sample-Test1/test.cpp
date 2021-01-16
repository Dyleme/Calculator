#include "pch.h"
#include "/programs/praktica/calculator/calculator/calculator/calc.h"
#include <stdlib.h>

TEST(TestCaseName, TestName) {
  EXPECT_EQ(3, calculate(TurnInPolish("1 + 2")));
  EXPECT_TRUE(true);
}
