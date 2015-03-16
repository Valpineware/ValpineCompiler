#include "Expression.h"

namespace ext
{
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


	void assertEqualComponents(const component_t *expected, const component_t *actual)
	{
		ASSERT_NOT_NULL(expected);
		ASSERT_NOT_NULL(actual);
		AssertEq_Throw(typeid(*expected), typeid(*actual));


		if (auto result = dynamic_cast<const innerExpression_t*>(expected))
			assertEqualResult(result, dynamic_cast<const innerExpression_t*>(actual));
		else if (auto oper = dynamic_cast<const operator_t*>(expected))
			assertEqualOperator(oper, dynamic_cast<const operator_t*>(actual));
		else if (auto id = dynamic_cast<const id_t*>(expected))
			assertEqualId(id, dynamic_cast<const id_t*>(actual));
		else if (auto arguments = dynamic_cast<const arguments_t*>(expected))
			assertEqualArguments(arguments, dynamic_cast<const arguments_t*>(actual));
	}


	void assertEqualComponentList(const componentList_t &expected, const componentList_t &actual)
	{
		ASSERT_EQ(expected.count(), expected.count());

		auto expectedIter = vc::makeIter(expected);
		auto actualIter = vc::makeIter(actual);

		while (expectedIter.hasNext())
		{
			assertEqualComponents(expectedIter.next(), actualIter.next());
		}
	}
}