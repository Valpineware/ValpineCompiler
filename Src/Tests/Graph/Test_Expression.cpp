#include "Tests.h"
#include ".Ext/Expression.h"

#define CLASS Test_Expression
using namespace ext;

TEST_CLASS
{
protected:
	void assertSingleIdentifier(const QString &expression)
	{
		Expression exp;
			addId(&exp, expression, id_t::Type::Basic);

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
	Expression exp;
		addId(&exp, "bar", id_t::Type::Basic);
		addOperator(&exp, "++");

	assertEqualExpression(exp, Expression("bar++"));
}


TEST_CASE(FunctionExpressionNoArguments)
{
	Expression exp;
		addId(&exp, "foo", id_t::Type::FunctionCall);
		addArguments(&exp);

	assertEqualExpression(exp, Expression("foo ()"));
}


TEST_CASE(FunctionExpressionSingleArgument1)
{
	Expression exp;
		addId(&exp, "barFoo", id_t::Type::FunctionCall);
		auto args = addArguments(&exp);
			auto arg1 = addExpression(args);
				addId(arg1, "size", id_t::Type::Basic);
				addOperator(arg1, "+");
				addId(arg1, "3", id_t::Type::Basic);

	assertEqualExpression(exp, Expression("barFoo(size+3)"));
}


TEST_CASE(FunctionExpressionSingleArgument2)
{
	Expression exp;
		addId(&exp, "calculate", id_t::Type::FunctionCall);
		auto args = addArguments(&exp);
			auto arg1 = addExpression(args);
				addId(arg1, "99", id_t::Type::Basic);
				addOperator(arg1, "/");
				auto res = addExpression(arg1);
					addId(res, "size", id_t::Type::Basic);
					addOperator(res, "+");
					addId(res, "3", id_t::Type::Basic);

	assertEqualExpression(exp, Expression("calculate (99 /(size + 3))"));
}


TEST_CASE(FunctionExpressionMultipleArguments)
{
	Expression exp;
		addId(&exp, "get_total_amount", id_t::Type::FunctionCall);
		auto args = addArguments(&exp);
			addId(args, "65", id_t::Type::Basic);
			addId(args, "value", id_t::Type::Basic);

	assertEqualExpression(exp, Expression("get_total_amount(65, value)"));
}


TEST_CASE(FunctionExpressionMultipleArgumentsNested)
{
	Expression exp;
		addId(&exp, "turnOn", id_t::Type::FunctionCall);
		auto args = addArguments(&exp);
			addId(args, "true", id_t::Type::Basic);
			auto arg2 = addExpression(args);
				addId(arg2, "foo", id_t::Type::FunctionCall);
				auto args2 = addArguments(arg2);
					addId(args2, "44", id_t::Type::Basic);
					addId(args2, "alpha", id_t::Type::Basic);

	assertEqualExpression(exp, Expression("turnOn(true, foo(44, alpha))"));
}