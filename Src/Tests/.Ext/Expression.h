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

	void assertId(component_t *component, const QString &expectedVerbatim, id_t::Type type);
	void assertArguments(component_t *component, const QString &expectedArg, int argCount);
	void assertOperator(component_t *component, const QString &expectedVerbatim);
	void assertEqualComponentList(const componentList_t &expected, const componentList_t &actual);
	void assertEqualResult(const innerExpression_t *expected, const innerExpression_t *actual);
	void assertEqualOperator(const operator_t *expected, const operator_t *actual);
	void assertEqualId(const id_t *expected, const id_t *actual);
	void assertEqualArguments(const arguments_t *expected, const arguments_t *actual);
	void assertEqualComponents(const component_t *expected, const component_t *actual);
	void assertEqualComponentList(const componentList_t &expected, const componentList_t &actual);

	template <typename T>
	void assertEqualExpression(const T &expected, const T &actual)
	{
		//TODO the verbatims aren't getting tested anywhere in this whole fancy test hierarchy
		assertEqualComponentList(expected.components(), actual.components());
	}
};

#endif
