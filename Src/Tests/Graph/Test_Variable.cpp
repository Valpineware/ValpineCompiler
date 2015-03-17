#include "Tests.h"
#include <Graph/Variable.h>

#define CLASS Test_Variable
using namespace vc::graph;

TEST_CLASS
{
};


TEST_CASE(Variable_WhatIs)
{
	#define IF(what) { Variable *v = Variable::make(what); Assert::NotNull(v);

	IF("int a;")
		Expect::EqStr("int", v->typeExpression().fullType());
		Expect::EqStr("a", v->id());
		Expect::EqStr("", v->initExpression());
	}


	IF("float b = 10.4f;")
		Expect::EqStr("float", v->typeExpression().fullType());
		Expect::EqStr("b", v->id());
		Expect::EqStr("10.4f", v->initExpression());
	}


	IF("bool isEnable = thing1.isEnabled() && thing2.isEnabled();")
		Expect::EqStr("bool", v->typeExpression().fullType());
		Expect::EqStr("isEnable", v->id());
		Expect::EqStr("thing1.isEnabled() && thing2.isEnabled()", v->initExpression());
	}


	IF("const MyType* _alamo= 77")	//intentionally no semi colon because we'll allow this to be considered a variable
									//obviously compile error later.
		Expect::EqStr("const MyType *", v->typeExpression().fullType());
		Expect::EqStr("_alamo", v->id());
		Expect::EqStr("77", v->initExpression());
	}

	#undef IF
}


TEST_CASE(Variable_WhatIsNot)
{
	#define tst(what) Assert::Null(Variable::make(what))

	tst("int bool a=10;");

	tst("return 0");
	tst("y++;");

	#undef tst
}