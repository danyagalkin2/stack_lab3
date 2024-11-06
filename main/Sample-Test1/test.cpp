#include "pch.h"
#include "stack.h"

TEST(TStack, can_create_stack_with_positive_args) {
	ASSERT_NO_THROW(TStack<int> s(5));
}

TEST(TStack, dont_create_stack_with_negative_args) {
	ASSERT_ANY_THROW(TStack<int> s(-4));
}

int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}