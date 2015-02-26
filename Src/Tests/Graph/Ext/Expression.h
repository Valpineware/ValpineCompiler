#include "../Tests.h"
#include <Graph/Expression.h>
using namespace vc::graph::expr;

namespace ext
{
	Id* addId(ComponentListUser *clu, const QString &idName, Id::Type idType)
	{
		auto id = Id::make(idName);
		id->setType(idType);
		clu->components().append(id);
		
		return id;
	}


	Operator* addOperator(ComponentListUser *clu, const QString &operatorVerbatim)
	{
		auto op = Operator::make(operatorVerbatim);
		clu->components().append(op);

		return op;
	}


	Expression* addResult(ComponentListUser *clu)
	{
		auto result = new Expression;
		clu->components().append(result);

		return result;
	}


	Arguments* addArguments(ComponentListUser *clu)
	{
		auto args = new Arguments();
		clu->components().append(args);

		return args;
	}


	Expression* addExpression(ComponentListUser *clu)
	{
		auto arg = new Expression;
		clu->components().append(arg);

		return arg;
	}


	void assertId(Component *component, const QString &expectedVerbatim, Id::Type type)
	{
		auto id = dynamic_cast<Id*>(component);
		ASSERT_NOT_NULL(id);
		EXPECT_EQ_STR(expectedVerbatim, id->verbatim());
		EXPECT_EQ(type, id->type());
	}


	void assertArguments(Component *component, const QString &expectedArg, int argCount)
	{
		auto args = dynamic_cast<Arguments*>(component);
		ASSERT_NOT_NULL(args);
		EXPECT_EQ_STR(expectedArg, args->verbatim());
		EXPECT_EQ(argCount, args->components().count());
	}


	void assertOperator(Component *component, const QString &expectedVerbatim)
	{
		auto op = dynamic_cast<Operator*>(component);
		ASSERT_NOT_NULL(op);
		EXPECT_EQ_STR(expectedVerbatim, op->verbatim());
	}


	void assertEqualComponentList(const ComponentList &expected, const ComponentList &actual);

	void assertEqualResult(const Expression *expected, const Expression *actual)
	{
		assertEqualComponentList(expected->components(), actual->components());
	}


	void assertEqualOperator(const Operator *expected, const Operator *actual)
	{
		EXPECT_EQ_STR(expected->verbatim(), actual->verbatim());
	}


	void assertEqualId(const Id *expected, const Id *actual)
	{
		EXPECT_EQ_STR(expected->verbatim(), actual->verbatim());
		EXPECT_EQ(expected->type(), actual->type());
	}


	void assertEqualArguments(const Arguments *expected, const Arguments *actual)
	{
		assertEqualComponentList(expected->components(), actual->components());
	}


	void assertEqualComponentList(const ComponentList &expected, const ComponentList &actual)
	{
		ASSERT_EQ(expected.count(), expected.count());

		auto expectedIter = vc::makeIter(expected);
		auto actualIter = vc::makeIter(actual);

		while (expectedIter.hasNext())
		{
			auto expectedComponent = expectedIter.next();
			auto actualComponent = actualIter.next();

			ASSERT_EQ(typeid(*expectedComponent), typeid(*actualComponent)) << "Components not of same type";

			if (auto result = dynamic_cast<Expression*>(expectedComponent))
				assertEqualResult(result, dynamic_cast<Expression*>(actualComponent));
			else if (auto oper = dynamic_cast<Operator*>(expectedComponent))
				assertEqualOperator(oper, dynamic_cast<Operator*>(actualComponent));
			else if (auto id = dynamic_cast<Id*>(expectedComponent))
				assertEqualId(id, dynamic_cast<Id*>(actualComponent));
			else if (auto arguments = dynamic_cast<Arguments*>(expectedComponent))
				assertEqualArguments(arguments, dynamic_cast<Arguments*>(actualComponent));
		}
	}


	void assertEqualExpression(const Expression &expected, const Expression &actual)
	{
		//TODO the verbatims aren't getting tested anywhere in this whole fancy test hierarchy
		assertEqualComponentList(expected.components(), actual.components());
	}
};