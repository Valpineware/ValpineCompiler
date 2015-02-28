#ifndef _test_ext_Expression_H
#define _test_ext_Expression_H

#include "../Tests.h"
#include <Graph/Expression.h>
using namespace vc::graph;

namespace ext
{
	using component_t = Expression::Component;
	using id_t = Expression::Id;
	using operator_t = Expression::Operator;
	using arguments_t = Expression::Arguments;
	using innerExpression_t = Expression::InnerExpression;

	using componentList_t = Expression::ComponentList;
	using componentListUser_t = Expression::ComponentListUser;

	template <typename T>
	id_t* addId(T *clu, const QString &idName, id_t::Type idType)
	{
		auto id = id_t::make(idName);
		id->setType(idType);
		clu->components().append(id);
		
		return id;
	}


	template <typename T>
	operator_t* addOperator(T *clu, const QString &operatorVerbatim)
	{
		auto op = operator_t::make(operatorVerbatim);
		clu->components().append(op);

		return op;
	}


	template <typename T>
	arguments_t* addArguments(T *clu)
	{
		auto args = new arguments_t;
		clu->components().append(args);

		return args;
	}


	template <typename T>
	innerExpression_t* addExpression(T *clu)
	{
		auto arg = new innerExpression_t;
		clu->components().append(arg);

		return arg;
	}


	void assertId(component_t *component, const QString &expectedVerbatim, id_t::Type type)
	{
		auto id = dynamic_cast<id_t*>(component);
		ASSERT_NOT_NULL(id);
		EXPECT_EQ_STR(expectedVerbatim, id->verbatim());
		EXPECT_EQ(type, id->type());
	}


	void assertArguments(component_t *component, const QString &expectedArg, int argCount)
	{
		auto args = dynamic_cast<arguments_t*>(component);
		ASSERT_NOT_NULL(args);
		EXPECT_EQ_STR(expectedArg, args->verbatim());
		EXPECT_EQ(argCount, args->components().count());
	}


	void assertOperator(component_t *component, const QString &expectedVerbatim)
	{
		auto op = dynamic_cast<operator_t*>(component);
		ASSERT_NOT_NULL(op);
		EXPECT_EQ_STR(expectedVerbatim, op->verbatim());
	}


	void assertEqualComponentList(const componentList_t &expected, const componentList_t &actual);

	void assertEqualResult(const innerExpression_t *expected, const innerExpression_t *actual)
	{
		assertEqualComponentList(expected->components(), actual->components());
	}


	void assertEqualOperator(const operator_t *expected, const operator_t *actual)
	{
		EXPECT_EQ_STR(expected->verbatim(), actual->verbatim());
	}


	void assertEqualId(const id_t *expected, const id_t *actual)
	{
		EXPECT_EQ_STR(expected->verbatim(), actual->verbatim());
		EXPECT_EQ(expected->type(), actual->type());
	}


	void assertEqualArguments(const arguments_t *expected, const arguments_t *actual)
	{
		assertEqualComponentList(expected->components(), actual->components());
	}


	void assertEqualComponentList(const componentList_t &expected, const componentList_t &actual)
	{
		ASSERT_EQ(expected.count(), expected.count());

		auto expectedIter = vc::makeIter(expected);
		auto actualIter = vc::makeIter(actual);

		while (expectedIter.hasNext())
		{
			auto expectedComponent = expectedIter.next();
			auto actualComponent = actualIter.next();

			ASSERT_NOT_NULL(expectedComponent);
			ASSERT_NOT_NULL(actualComponent);
			ASSERT_EQ(typeid(*expectedComponent), typeid(*actualComponent)) << "Components not of same type";

			if (auto result = dynamic_cast<innerExpression_t*>(expectedComponent))
				assertEqualResult(result, dynamic_cast<innerExpression_t*>(actualComponent));
			else if (auto oper = dynamic_cast<operator_t*>(expectedComponent))
				assertEqualOperator(oper, dynamic_cast<operator_t*>(actualComponent));
			else if (auto id = dynamic_cast<id_t*>(expectedComponent))
				assertEqualId(id, dynamic_cast<id_t*>(actualComponent));
			else if (auto arguments = dynamic_cast<arguments_t*>(expectedComponent))
				assertEqualArguments(arguments, dynamic_cast<arguments_t*>(actualComponent));
		}
	}


	template <typename T>
	void assertEqualExpression(const T &expected, const T &actual)
	{
		//TODO the verbatims aren't getting tested anywhere in this whole fancy test hierarchy
		assertEqualComponentList(expected.components(), actual.components());
	}
};

#endif
