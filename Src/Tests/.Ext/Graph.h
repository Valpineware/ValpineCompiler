#ifndef _test_ext_Graph_H
#define _test_ext_Graph_H

#include "../Tests.h"
#include "Expression.h"
#include <Graph/Graph.h>
using namespace vc::graph;

namespace ext
{
	Statement* addStatement(Block &block, Statement *statement)
	{
		block.appendStatement(statement);
		return statement;
	}


	Preprocessor* addPreprocessor(Block &block, Preprocessor *preprocessor)
	{
		block.appendStatement(preprocessor);
		return preprocessor;
	}


	Class* addClass(Block &block, Class *cls)
	{
		block.appendStatement(cls);
		return cls;
	}


	ControlStructure* addControlStructure(Block &block, ControlStructure *controlStructure)
	{
		block.appendStatement(controlStructure);
		return controlStructure;
	}


	Expression* addExpression(Block &block,  Expression *expression)
	{
		block.appendStatement(expression);
		return expression;
	}


	Function* addFunction(Block &block, Function *function)
	{
		block.appendStatement(function);
		return function;
	}


	Variable* addVariable(Block &block, Variable *variable)
	{
		block.appendStatement(variable);
		return variable;
	}


	void assertEqualPreprocessor(Preprocessor *expected, Preprocessor *actual)
	{
		EXPECT_EQ_STR(expected->verbatim(), actual->verbatim());
	}


	template <typename T>
	void assertSameLists(const QList<T> &list1, const QList<T> &list2)
	{
		ASSERT_EQ(list1.count(), list2.count());
		{
			auto expectIter = vc::makeIter(list1);
			auto actualIter = vc::makeIter(list2);

			while (expectIter.hasNext())
			{
				ASSERT_EQ(expectIter.next(), actualIter.next());
			}
		}
	};


	void assertEqualClass(Class *expected, Class *actual)
	{
		EXPECT_EQ_STR(expected->id(), actual->id());

		assertSameLists(expected->superClasses(), actual->superClasses());
		assertSameLists(expected->interfaces(), actual->interfaces());
		assertSameLists(expected->members(), actual->members());
	}


	void assertEqualBlock(const Block &expected, const Block &actual);


	void assertEqualControlStructure(ControlStructure *expected, ControlStructure *actual)
	{
		EXPECT_EQ_STR(expected->name(), actual->name());
		assertEqualBlock(expected->block(), actual->block());
	}


	void assertEqualFunction(Function *expected, Function *actual)
	{
		EXPECT_EQ_STR(expected->id(), actual->id());
		EXPECT_EQ(expected->returnType(), actual->returnType());
		EXPECT_EQ(expected->parameters(), actual->parameters());
		assertEqualBlock(expected->block(), actual->block());
	}


	void assertEqualVariable(Variable *expected, Variable *actual)
	{
		EXPECT_EQ_STR(expected->id(), actual->id());
		EXPECT_EQ_STR(expected->initExpression(), actual->initExpression());
	}


	void assertEqualBlock(const Block &expected, const Block &actual)
	{
		auto expectedIter = vc::makeIter(expected.statements());
		auto actualIter = vc::makeIter(actual.statements());

		while (expectedIter.hasNext())
		{
			Statement *expectedStatement = expectedIter.next();
			Statement *actualStatement = actualIter.next();

			ASSERT_NOT_NULL(expectedStatement);
			ASSERT_NOT_NULL(actualStatement);


			if (typeid(*expectedStatement) != typeid(*actualStatement))
				qDebug() << "Types are not the same";

			ASSERT_EQ(typeid(*expectedStatement), typeid(*actualStatement)) << "Statements not of same type";

			if (auto preprocessor = dynamic_cast<Preprocessor*>(expectedStatement))
				assertEqualPreprocessor(preprocessor, dynamic_cast<Preprocessor*>(actualStatement));

			else if (auto cls = dynamic_cast<Class*>(expectedStatement))
				assertEqualClass(cls, dynamic_cast<Class*>(actualStatement));

			else if (auto controlStructure = dynamic_cast<ControlStructure*>(expectedStatement))
				assertEqualControlStructure(controlStructure, dynamic_cast<ControlStructure*>(actualStatement));

			else if (auto expression = dynamic_cast<Expression*>(expectedStatement))
				assertEqualExpression(*expression, *dynamic_cast<Expression*>(actualStatement));

			else if (auto function = dynamic_cast<Function*>(expectedStatement))
				assertEqualFunction(function, dynamic_cast<Function*>(actualStatement));

			else if (auto variable = dynamic_cast<Variable*>(expectedStatement))
				assertEqualVariable(variable, dynamic_cast<Variable*>(expectedStatement));
		}
	}
};

#endif
