#include "Tests.h"
#include <Graph/Variable.h>

#define CLASS Test_Variable
using namespace vc::graph;

TEST_CLASS
{
};


TEST_CASE(Variable_WhatIs)
{
	#define IF(what) { Variable *v = Variable::createFromVerbatimSignature(what); ASSERT_NOT_NULL(v);

	IF("int a;")
		EXPECT_EQ("int", v->typeExpression().fullType());
		EXPECT_EQ("a", v->id());
		EXPECT_EQ("", v->initExpression());
	}


	IF("float b = 10.4f;")
		EXPECT_EQ("float", v->typeExpression().fullType());
		EXPECT_EQ("b", v->id());
		EXPECT_EQ("10.4f", v->initExpression());
	}


	IF("bool isEnable = thing1.isEnabled() && thing2.isEnabled();")
		EXPECT_EQ("bool", v->typeExpression().fullType());
		EXPECT_EQ("isEnable", v->id());
		EXPECT_EQ("thing1.isEnabled() && thing2.isEnabled()", v->initExpression());
	}


	IF("const MyType* _alamo= 77")	//intentionally no semi colon because we'll allow this to be considered a variable
									//obviously compile error later.
		EXPECT_EQ("const MyType *", v->typeExpression().fullType());
		EXPECT_EQ("_alamo", v->id());
		EXPECT_EQ("77", v->initExpression());
	}

	#undef IF
}


TEST_CASE(Variable_WhatIsNot)
{
	#define tst(what) ASSERT_NULL(Variable::createFromVerbatimSignature(what))

	tst("int bool a=10;");

	#undef tst
}