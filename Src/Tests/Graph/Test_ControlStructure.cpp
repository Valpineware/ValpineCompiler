#include "Tests.h"
#include <Graph/ControlStructure.h>

#define CLASS Test_ControlStructure
using namespace vc;

TEST_CLASS
{
protected:
	graph::ControlStructure* test(const QString &what)
	{
		graph::ControlStructure *cs = graph::ControlStructure::make(what);
		if (cs == nullptr)
			qFatal("Null control structure in Test_ControlStructure");

		return cs;
	}
};


TEST_CASE(FunctionHeader_WhatIs)
{
	#define IF(what) { graph::ControlStructure *cs = test(what);

	IF ("for (int i=0; i<100; i++)")
		Expect::EqStr("for", cs->name());
		Expect::EqStr("int i=0; i<100; i++", cs->expression());
	}

	IF ("while ( true && false || true)")
		Expect::EqStr("while", cs->name());
		Expect::EqStr(" true && false || true", cs->expression());
	}

	IF ("if (b > 42 && myName != \"Dan\")")
		Expect::EqStr("if", cs->name());
		Expect::EqStr("b > 42 && myName != \"Dan\"", cs->expression());
	}

	IF ("else if ( (true) || (a + b < 90))")
		Expect::EqStr("else if", cs->name());
		Expect::EqStr(" (true) || (a + b < 90)", cs->expression());
	}

	IF ("else")
		Expect::EqStr("else", cs->name());
		Expect::EqStr("", cs->expression());
	}

	IF ("defer while (foo() > 42)")
		Expect::EqStr("defer while", cs->name());
		Expect::EqStr("foo() > 42", cs->expression());
	}

	#undef IF
}


TEST_CASE(FunctionHeader_WhatIsNot)
{
	const QString header = "void process()";

	#define tst(what) Assert::Null(graph::ControlStructure::make(what))

	tst("for for (true)");
	tst("whil (thisExpression == false)");
	tst("if (i < 99");
	tst("else (false)");

	#undef tst
}