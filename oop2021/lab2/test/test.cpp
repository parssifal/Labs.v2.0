#include <lab2>
#include <gtest/gtest.h>

TEST(Buth_Lemn, Positive) {
	Buth_Lemn l(3, 1);

	EXPECT_NEAR(l.type());
	EXPECT_NEAR(l.parametrs());
	EXPECT_NEAR(l.area());
	EXPECT_NEAR(l.distance());
	EXPECT_NEAR(l.frm);
}

