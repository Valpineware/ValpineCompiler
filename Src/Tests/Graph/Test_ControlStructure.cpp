#include "../.Ext/Graph.h"
#include <Graph/ControlStructure.h>

#define CLASS Test_ControlStructure
using namespace vc;

TEST_CLASS
{
protected:
	void assertBuild(const QString &verbatim, const QString &expectedName, const QList<Statement*> expectedExpressionList)
	{
		graph::ControlStructure *cs = ControlStructure::make(verbatim);
		Assert::NotNull(cs);
		Expect::EqStr(expectedName, cs->name());
		assertEqualStatementLists(expectedExpressionList, cs->expressionList());
	}
};

TEST_CASE(Build_For)
{
	assertBuild("for (int i=0; i<100; i++)", "for",
				QList<Statement*>() << Variable::make("int i=0")
									<< new Expression("i<100")
									<< new Expression("i++"));
}


TEST_CASE(Build_While)
{
	assertBuild("while ( true && false || true)", "while",
				QList<Statement*>() << new Expression(" true && false || true"));
}


TEST_CASE(Build_If)
{
	assertBuild("if (b > 42 && myName != \"Dan\")", "if",
				QList<Statement*>() << new Expression("b > 42 && myName != \"Dan\""));
}


TEST_CASE(Build_ElseIf)
{
	assertBuild("else if ( true || (a + b < 90))", "else if", 
				QList<Statement*>() << new Expression(" true || (a + b < 90)"));
}


TEST_CASE(Build_Else)
{
	assertBuild("else", "else", QList<Statement*>());
}


TEST_CASE(Build_DeferWhile)
{
	assertBuild("defer while (foo() > 42)", "defer while",
				QList<Statement*>() << new Expression("foo() > 42"));
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