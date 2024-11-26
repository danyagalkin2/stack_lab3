#include "pch.h"
#include "stack.h"

TEST(TStack, can_create_stack_with_positive_args) {
	ASSERT_NO_THROW(TStack<int> s(5));
}

TEST(TStack, dont_create_stack_with_negative_args) {
	ASSERT_ANY_THROW(TStack<int> s(-4));
}

TEST(TStack, PushTest) {
	TStack<int> stack;
	stack.Push(10);
	EXPECT_EQ(stack.Top(), 10);
}

TEST(TStack, PopTest) {
	TStack<int> s;
	s.Push(10);
	EXPECT_EQ(s.Pop(), 10);
	EXPECT_TRUE(s.isEmpty());
}

TEST(TStack, PopEmptyStack) {
	TStack<int> s;
	ASSERT_ANY_THROW(s.Pop());
}

TEST(TStack, TopTest) {
    TStack<int> stack;
    stack.Push(30);
    EXPECT_EQ(stack.Top(), 30);
    stack.Push(40);
    EXPECT_EQ(stack.Top(), 40);
}


TEST(TStack, TopEmptyStackTest) {
    TStack<int> stack;
    ASSERT_ANY_THROW(stack.Top());
}



TEST(TStack, NoEqStacks) {
	TStack<int> a, b;
	a.Push(1);
	a.Push(1);
	a.Push(1);

	b.Push(2);
	b.Push(2);
	b.Push(2);

	ASSERT_NE(a, b);

}

TEST(TStack, CompareEqualStacks)
{
	TStack<int> a(3);
	TStack<int> b(3);
	a.Push(2);
	b.Push(2);
	EXPECT_TRUE(a == b);
}

TEST(TStack, CheckFullStack)
{
	TStack<int> a(2);
	a.Push(10);
	a.Push(20);
	EXPECT_TRUE(a.isFull());
}

TEST(TStack, CanClearNoNEmptyStack)
{
	TStack<int> a(5);
	a.Push(1);
	a.Push(2);
	a.Push(3);
	a.Clear();
	EXPECT_TRUE(a.isEmpty());
	EXPECT_ANY_THROW(a.Pop());
}

TEST(TStack, CopyStack)
{
	TStack<int> b(2);
	b.Push(1);
	b.Push(2);
	TStack<int> a(b);
	a.Pop();
	b.Pop();
	EXPECT_EQ(a,b);
}

TEST(TCalc, test1) 
{
	TCalc c;
	c.setInfix("1+2");
	c.ToPostfix();
	EXPECT_EQ(c.getPostfix(), "1 2 +");
	EXPECT_EQ(c.CalcPostfix(), 3);

}

TEST(TCalc, test2)
{
	TCalc c;
	c.setInfix("1+2*(3-2)-4");
	c.ToPostfix();
	EXPECT_EQ(c.getPostfix(), "1 2 3 2 - * + 4 -");
	EXPECT_EQ(c.CalcPostfix(), -1);

}

TEST(TCalc, test3)
{
	TCalc c;
	c.setInfix("(((1+23)*1-22)+5)*2-(7");
	ASSERT_ANY_THROW(c.Calc());
}

TEST(TCalc, test4)
{
	TCalc c;
	c.setInfix("(((1+23)*1-22)+5)*2-7");
	EXPECT_EQ(c.Calc(), 7);

}

TEST(TCalc, test5)
{
	TCalc c;
	c.setInfix("20+10*3-4+(1+2)/3-8");
	c.ToPostfix();
	EXPECT_EQ(c.Calc(), 39);
	EXPECT_EQ(c.getPostfix(), "20 10 3 * + 4 - 1 2 + 3 / + 8 -");

}




int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}