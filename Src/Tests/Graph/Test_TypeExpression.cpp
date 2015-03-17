#include "Tests.h"
#include <Graph/TypeExpression.h>

#define CLASS Test_TypeExpresion
using namespace vc::graph;


TEST_CLASS
{
};



TEST_CASE(test1)
{
	TypeExpression te("const int &");
	Expect::Eq(te.baseType(), "int");
	Expect::Eq(te.preModifiers()[0], "const");
	Expect::Eq(te.postModifiers()[0], "&");
}


TEST_CASE(test2)
{
	TypeExpression te("MyCrazy_TypeThings1241326*&&* const *");
	Expect::Eq(te.baseType(), "MyCrazy_TypeThings1241326");
	EXPECT_TRUE(te.preModifiers().isEmpty());
	Expect::Eq(te.postModifiers()[0], "*");
	Expect::Eq(te.postModifiers()[1], "&");
	Expect::Eq(te.postModifiers()[2], "&");
	Expect::Eq(te.postModifiers()[3], "*");
	Expect::Eq(te.postModifiers()[4], "const");
}