#include "Tests.h"
#include <Parser/Recognizer.h>
#include <regex>


#define CLASS Test_Recognizer
using namespace vc;

TEST_CLASS
{
};


TEST_CASE(FunctionHeader_WhatIs)
{
	#define tst(what) ASSERT_TRUE(parser::Recognizer::isFunctionHeader(what))

	tst("void simple()");
	tst("int		 wacky	( ) ");
	tst(" bool	isCool(  )");
	tst("		float __compilerFunction ()");
	tst("		double whatIsPi(		)");


	#undef tst
}


TEST_CASE(FunctionHeader_WhatIsNot)
{
	const QString header = "void process()";
}
