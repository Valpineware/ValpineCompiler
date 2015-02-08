#include "Tests.h"
#include <Graph/ControlStructure.h>

#define CLASS Test_ControlStructure
using namespace vc;

TEST_CLASS
{
protected:
	graph::ControlStructure* test(const QString &what)
	{
		graph::ControlStructure *cs = graph::ControlStructure::createFromVerbatimSignature(what);
		if (cs == nullptr)
			qFatal("Null control structure in Test_ControlStructure");

		return cs;
	}
};


TEST_CASE(FunctionHeader_WhatIs)
{
	#define IF(what) { graph::ControlStructure *cs = test(what);

	IF ("for (int i=0; i<100; i++)")
		EXPECT_EQ_STR("for", cs->name());
		EXPECT_EQ_STR("int i=0; i<100; i++", cs->expression());
	}

	IF ("while ( true && false || true)")
		EXPECT_EQ_STR("while", cs->name());
		EXPECT_EQ_STR(" true && false || true", cs->expression());
	}

	IF ("if (b > 42 && myName != \"Dan\")")
		EXPECT_EQ_STR("if", cs->name());
		EXPECT_EQ_STR("b > 42 && myName != \"Dan\"", cs->expression());
	}

	IF ("elseif ( (true) || (a + b < 90))")
		EXPECT_EQ_STR("elseif", cs->name());
		EXPECT_EQ_STR(" (true) || (a + b < 90)", cs->expression());
	}

	IF ("else")
		EXPECT_EQ_STR("else", cs->name());
		EXPECT_EQ_STR("", cs->expression());
	}

	#undef IF
}


TEST_CASE(FunctionHeader_WhatIsNot)
{
	const QString header = "void process()";

	#define tst(what) ASSERT_NULL(graph::ControlStructure::createFromVerbatimSignature(what))

	tst("for for (true)");
	tst("whil (thisExpression == false)");
	tst("if (i < 99");

	#undef tst
}