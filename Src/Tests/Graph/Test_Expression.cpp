#include "Tests.h"
#include "Ext/Expression.h"

#define CLASS Test_Expression
using namespace vc::graph::expression;
using namespace ext;

TEST_CLASS
{
protected:
	void assertSingleIdentifier(const QString &expression)
	{
		Expression exp("");
			addId(exp.components(), expression, Id::Type::Basic);

		assertEqualExpression(exp, Expression(expression));
	}
};


TEST_CASE(SingleResult1)
{
	assertSingleIdentifier("10");
}


TEST_CASE(SingleResult2)
{
	assertSingleIdentifier("foo");
}


TEST_CASE(IdentifierAndOperator)
{
	Expression exp("");
		addId(exp.components(), "bar", Id::Type::Basic);
		addOperator(exp.components(), "++");

	assertEqualExpression(exp, Expression("bar++"));
}


TEST_CASE(FunctionExpressionNoArguments)
{
	Expression exp("");
		addId(exp.components(), "foo", Id::Type::FunctionCall);
		addArguments(exp.components());

	assertEqualExpression(exp, Expression("foo ()"));
}


TEST_CASE(FunctionExpressionSingleArgument1)
{
	Expression exp("");
		addId(exp.components(), "barFoo", Id::Type::FunctionCall);
		auto args = addArguments(exp.components());
			auto arg1 = addArgument(args);
				addId(arg1->components(), "size", Id::Type::Basic);
				addOperator(arg1->components(), "+");
				addId(arg1->components(), "3", Id::Type::Basic);

	assertEqualExpression(exp, Expression("barFoo(size+3)"));
}


TEST_CASE(FunctionExpressionSingleArgument2)
{
	Expression exp("");
		addId(exp.components(), "calculate", Id::Type::FunctionCall);
		auto args = addArguments(exp.components());
			auto arg1 = addArgument(args);
				addId(arg1->components(), "99", Id::Type::Basic);
				addOperator(arg1->components(), "/");
				auto res = addResult(arg1->components());
					addId(res->components(), "size", Id::Type::Basic);
					addOperator(res->components(), "+");
					addId(res->components(), "3", Id::Type::Basic);

	assertEqualExpression(exp, Expression("calculate (99 /(size + 3))"));
}


TEST_CASE(FunctionExpressionMultipleArguments)
{
	Expression exp("");
		addId(exp.components(), "get_total_amount", Id::Type::FunctionCall);
		auto args = addArguments(exp.components());
			auto arg1 = addArgument(args);
				addId(arg1->components(), "65", Id::Type::Basic);
			auto arg2 = addArgument(args);
				addId(arg2->components(), "value", Id::Type::Basic);

	assertEqualExpression(exp, Expression("get_total_amount(65, value)"));
}


TEST_CASE(FunctionExpressionMultipleArgumentsNested)
{
	Expression("foo(a,b,c)");

	Expression exp("");
		addId(exp.components(), "turnOn", Id::Type::FunctionCall);
		auto args = addArguments(exp.components());
			auto arg1 = addArgument(args);
				addId(arg1->components(), "true", Id::Type::Basic);
			auto arg2 = addArgument(args);
				addId(arg2->components(), "foo", Id::Type::FunctionCall);
				auto args2 = addArguments(arg2->components());
					auto arg2_1 = addArgument(args2);
						addId(arg2_1->components(), "44", Id::Type::Basic);
					auto arg2_2 = addArgument(args2);
						addId(arg2_2->components(), "alpha", Id::Type::Basic);

	assertEqualExpression(exp, Expression("turnOn(true, foo(44, alpha))"));
}