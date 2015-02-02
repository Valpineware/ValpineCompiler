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
	EXPECT_EQ(te.baseType(), "int");
	EXPECT_EQ(te.preModifiers()[0], "const");
	EXPECT_EQ(te.postModifiers()[0], "&");
}


TEST_CASE(test2)
{
	TypeExpression te("MyCrazy_TypeThings1241326*&&* const *");
	EXPECT_EQ(te.baseType(), "MyCrazy_TypeThings1241326");
	EXPECT_TRUE(te.preModifiers().isEmpty());
	EXPECT_EQ(te.postModifiers()[0], "*");
	EXPECT_EQ(te.postModifiers()[1], "&");
	EXPECT_EQ(te.postModifiers()[2], "&");
	EXPECT_EQ(te.postModifiers()[3], "*");
	EXPECT_EQ(te.postModifiers()[4], "const");
}