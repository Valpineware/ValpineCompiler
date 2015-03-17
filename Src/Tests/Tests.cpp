#include "Tests.h"

#include <fstream>

bool Assert::mFatalOnAssert = true;
bool Expect::mFatalOnExpect = true;


int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}