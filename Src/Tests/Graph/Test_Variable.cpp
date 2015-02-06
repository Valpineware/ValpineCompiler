#include "Tests.h"
#include <Graph/Variable.h>

#define CLASS Test_Variable
using namespace vc::graph;

TEST_CLASS
{
};


TEST_CASE(Variable_WhatIs)
{
	#define tst(what) ASSERT_NOT_NULL(Variable::createFromVerbatimSignature(what))

	tst("int a");
	tst("float b = 10.4f");
	tst("bool isEnable = thing1.isEnabled() && thing2.isEnabled()");

	#undef tst
}


TEST_CASE(Variable_WhatIsNot)
{
	#define tst(what) ASSERT_NULL(Variable::createFromVerbatimSignature(what))

	#undef tst
}