#include "actapch.h"
#include "catch.hpp"

TEST_CASE("SampleTest", "SampleTestOnly")
{
	SECTION("FirstCase")
	{
		REQUIRE(0 == 0);
	}
	SECTION("SecondCase")
	{
		REQUIRE(false == false);
	}
}