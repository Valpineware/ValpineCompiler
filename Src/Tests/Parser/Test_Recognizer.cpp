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
	#define tst(what) ASSERT_NOT_NULL(parser::Recognizer::parseFunctionSignature(what))

	tst("void simple()");
	tst("int		 wacky	( ) ");
	tst(" bool	isCool(  )");
	tst("		float __compilerFunction ()");
	tst("		double whatIsPi(		)");

	tst(" int* pointer1()");
	tst(" *** void ** crazyPointerThatWontActuallyCompileButShouldLookLikeAFunction()");		//TODO should this look like function and flag as an error later, or just not even be considered a function?
	tst("const double& cosntRefPlease()");
	tst("	const void		* const *	const	*& superLongPointerRefThing()");

	tst("QString what()");
	tst("const __MyWeirdTyPe_________ *** _function_Name_Is_Here ( )");

	tst("void singleParameter(int p1)");
	tst("void defaultParameter(int count=12)");

	#undef tst
}


TEST_CASE(FunctionHeader_WhatIsNot)
{
	const QString header = "void process()";

	#define tst(what) ASSERT_NULL(parser::Recognizer::parseFunctionSignature(what))

	tst("123Type doesNotWork()");
	tst("NoGo 999Function		( )");
	tst("Don't useWeirdSybols()");
	tst("Ever !()");

	tst("float Not A Function()");
	tst("float functionDeclarationsDontExistInValpine() ;");

	#undef tst
}
