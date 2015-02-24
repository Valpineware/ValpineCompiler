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
		EXPECT_EQ_STR("int", v->typeExpression().fullType());
		EXPECT_EQ_STR("a", v->id());
		EXPECT_EQ_STR("", v->initExpression());
	}


	IF("float b = 10.4f;")
		EXPECT_EQ_STR("float", v->typeExpression().fullType());
		EXPECT_EQ_STR("b", v->id());
		EXPECT_EQ_STR("10.4f", v->initExpression());
	}


	IF("bool isEnable = thing1.isEnabled() && thing2.isEnabled();")
		EXPECT_EQ_STR("bool", v->typeExpression().fullType());
		EXPECT_EQ_STR("isEnable", v->id());
		EXPECT_EQ_STR("thing1.isEnabled() && thing2.isEnabled()", v->initExpression());
	}


	IF("const MyType* _alamo= 77")	//intentionally no semi colon because we'll allow this to be considered a variable
									//obviously compile error later.
		EXPECT_EQ_STR("const MyType *", v->typeExpression().fullType());
		EXPECT_EQ_STR("_alamo", v->id());
		EXPECT_EQ_STR("77", v->initExpression());
	}

	#undef IF
}


TEST_CASE(Variable_WhatIsNot)
{
	#define tst(what) ASSERT_NULL(Variable::createFromVerbatimSignature(what))

	tst("int bool a=10;");

	tst("return 0");
	tst("y++;");

	#undef tst
}