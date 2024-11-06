#include "pch.h"
#include "stack.h"

TEST(TStack, TestName) {
  ASSERT_ANY_THROW(TStack<int> s(4));
}