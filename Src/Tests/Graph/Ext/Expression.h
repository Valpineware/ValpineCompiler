#include "../Tests.h"
#include <Graph/Expression.h>
using namespace vc::graph::expression;

namespace ext
{
	Id* addId(ComponentList &list, const QString &idName, Id::Type idType)
	{
		auto id = new Id(idName);
		id->setType(idType);
		list.append(id);
		
		return id;
	}


	Operator* addOperator(ComponentList &list, const QString &operatorVerbatim)
	{
		auto op = new Operator(operatorVerbatim);
		list.append(op);

		return op;
	}


	Expression* addResult(ComponentList &list)
	{
		auto result = new Expression("");
		list.append(result);

		return result;
	}


	Arguments* addArguments(ComponentList &list)
	{
		auto args = new Arguments("");
		list.append(args);

		return args;
	}


	Expression* addArgument(Arguments *arguments)
	{
		auto arg = new Expression("");
		arguments->components().append(arg);

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
		ASSERT_EQ(expected->components().count(), actual->components().count());

		auto expectedIter = vc::makeIter(expected->components());
		auto actualIter = vc::makeIter(actual->components());

		while (expectedIter.hasNext())
		{
			assertEqualResult(dynamic_cast<Expression*>(expectedIter.next()),
							  dynamic_cast<Expression*>(actualIter.next()));
		}
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