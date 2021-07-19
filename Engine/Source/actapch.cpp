#include "actapch.h"
#include "catch.hpp"


// you only need to write the TEST_CASE(string, string) [PASSED STRING WON'T CAUSE ANY PROBLEM]
// should you erase the SECTION(string) part, there won't be any problem
// but you'd better put it for a better understanding between programmer(s)
TEST_CASE("SampleTest")
{
	REQUIRE(2 == 2);
	SECTION("First")
	{
		REQUIRE(false == false);
	}
}
TEST_CASE("SampleUnitTest", "StringValueTesting")
{
	SECTION("Second")
	{
		REQUIRE("you" == "you");
	}
	SECTION("This Sample Case Is Indeed WRONG")
	{
		REQUIRE("you" == "are");
	}
}