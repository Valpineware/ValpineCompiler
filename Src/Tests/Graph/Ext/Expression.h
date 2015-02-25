#include <Graph/Expression.h>
using namespace vc::graph;

namespace ext
{
	Expression::Id* addId(Expression::ComponentList &list, const QString &idName, Expression::Id::Type idType)
	{
		auto id = new Expression::Id(idName);
		id->setType(idType);
		list.append(id);
		
		return id;
	}


	Expression::Operator* addOperator(Expression::ComponentList &list, const QString &operatorVerbatim)
	{
		auto op = new Expression::Operator(operatorVerbatim);
		list.append(op);

		return op;
	}


	Expression::Result* addResult(Expression::ComponentList &list)
	{
		auto result = new Expression::Result("");
		list.append(result);

		return result;
	}


	Expression::Arguments* addArguments(Expression::ComponentList &list)
	{
		auto args = new Expression::Arguments("");
		list.append(args);

		return args;
	}


	Expression::Result* addArgument(Expression::Arguments *arguments)
	{
		auto arg = new Expression::Result("");
		arguments->list().append(arg);

		return arg;
	}


	void assertId(Expression::Component *component, const QString &expectedVerbatim, Expression::Id::Type type)
	{
		auto id = dynamic_cast<Expression::Id*>(component);
		ASSERT_NOT_NULL(id);
		EXPECT_EQ_STR(expectedVerbatim, id->verbatim());
		EXPECT_EQ(type, id->type());
	}


	void assertArguments(Expression::Component *component, const QString &expectedArg, int argCount)
	{
		auto args = dynamic_cast<Expression::Arguments*>(component);
		ASSERT_NOT_NULL(args);
		EXPECT_EQ_STR(expectedArg, args->verbatim());
		EXPECT_EQ(argCount, args->list().count());
	}


	void assertOperator(Expression::Component *component, const QString &expectedVerbatim)
	{
		auto op = dynamic_cast<Expression::Operator*>(component);
		ASSERT_NOT_NULL(op);
		EXPECT_EQ_STR(expectedVerbatim, op->verbatim());
	}


	void assertEqualComponentList(const Expression::ComponentList &expected, const Expression::ComponentList &actual);

	void assertEqualResult(const Expression::Result *expected, const Expression::Result *actual)
	{
		assertEqualComponentList(expected->components(), actual->components());
	}


	void assertEqualOperator(const Expression::Operator *expected, const Expression::Operator *actual)
	{
		EXPECT_EQ_STR(expected->verbatim(), actual->verbatim());
	}


	void assertEqualId(const Expression::Id *expected, const Expression::Id *actual)
	{
		EXPECT_EQ_STR(expected->verbatim(), actual->verbatim());
		EXPECT_EQ(expected->type(), actual->type());
	}


	void assertEqualArguments(const Expression::Arguments *expected, const Expression::Arguments *actual)
	{
		ASSERT_EQ(expected->list().count(), actual->list().count());

		auto expectedIter = vc::makeIter(expected->list());
		auto actualIter = vc::makeIter(actual->list());

		while (expectedIter.hasNext())
		{
			assertEqualResult(dynamic_cast<Expression::Result*>(expectedIter.next()),
							  dynamic_cast<Expression::Result*>(actualIter.next()));
		}
	}


	void assertEqualComponentList(const Expression::ComponentList &expected, const Expression::ComponentList &actual)
	{
		ASSERT_EQ(expected.count(), expected.count());

		auto expectedIter = vc::makeIter(expected);
		auto actualIter = vc::makeIter(actual);

		while (expectedIter.hasNext())
		{
			auto expectedComponent = expectedIter.next();
			auto actualComponent = actualIter.next();

			ASSERT_EQ(typeid(*expectedComponent), typeid(*actualComponent)) << "Components not of same type";

			if (auto result = dynamic_cast<Expression::Result*>(expectedComponent))
				assertEqualResult(result, dynamic_cast<Expression::Result*>(actualComponent));
			else if (auto oper = dynamic_cast<Expression::Operator*>(expectedComponent))
				assertEqualOperator(oper, dynamic_cast<Expression::Operator*>(actualComponent));
			else if (auto id = dynamic_cast<Expression::Id*>(expectedComponent))
				assertEqualId(id, dynamic_cast<Expression::Id*>(actualComponent));
			else if (auto arguments = dynamic_cast<Expression::Arguments*>(expectedComponent))
				assertEqualArguments(arguments, dynamic_cast<Expression::Arguments*>(actualComponent));
		}
	}


	void assertEqualExpression(const Expression &expected, const Expression &actual)
	{
		//TODO the verbatims aren't getting tested anywhere in this whole fancy test hierarchy
		assertEqualComponentList(expected.components(), actual.components());
	}
};