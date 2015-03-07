#include "Graph.h"

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


	void assertEqualBlock(const Block &expected, const Block &actual);
	void assertEqualStatement(Statement *expected, Statement *actual);


	void assertEqualPreprocessor(Preprocessor *expected, Preprocessor *actual)
	{
		EXPECT_EQ_STR(expected->verbatim(), actual->verbatim());
	}


	void assertEqualClass(Class *expected, Class *actual)
	{
		EXPECT_EQ_STR(expected->id(), actual->id());

		auto assertAccessIdPair = [](const Class::AccessIdPair &lhs, const Class::AccessIdPair &rhs) -> void
		{
			EXPECT_EQ_STR(lhs.id, rhs.id);
			EXPECT_EQ(lhs.accessType, rhs.accessType);
		};

		assertSameLists<Class::AccessIdPair>(expected->superClasses(), actual->superClasses(), assertAccessIdPair);
		assertSameLists<Class::AccessIdPair>(expected->interfaces(), actual->interfaces(), assertAccessIdPair);
		assertSameLists<Class::Member*>(expected->members(), actual->members(),
										[](const Class::Member *lhs, const Class::Member *rhs) -> void
										{
											ASSERT_EQ(lhs->accessType, rhs->accessType);
											assertEqualStatement(lhs->statement, rhs->statement);
										});
	}


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


			assertEqualStatement(expectedStatement, actualStatement);
		}
	}


	void assertEqualStatement(Statement *expected, Statement *actual)
	{
		ASSERT_NOT_NULL(expected);
		ASSERT_NOT_NULL(actual);

		if (typeid(*expected) != typeid(*actual))
			qDebug() << "Types are not the same";

		ASSERT_EQ(typeid(*expected), typeid(*actual)) << "Statements not of same type";

		if (auto preprocessor = dynamic_cast<Preprocessor*>(expected))
			assertEqualPreprocessor(preprocessor, dynamic_cast<Preprocessor*>(actual));

		else if (auto cls = dynamic_cast<Class*>(expected))
			assertEqualClass(cls, dynamic_cast<Class*>(actual));

		else if (auto controlStructure = dynamic_cast<ControlStructure*>(expected))
			assertEqualControlStructure(controlStructure, dynamic_cast<ControlStructure*>(actual));

		else if (auto expression = dynamic_cast<Expression*>(expected))
			assertEqualExpression(*expression, *dynamic_cast<Expression*>(actual));

		else if (auto function = dynamic_cast<Function*>(expected))
			assertEqualFunction(function, dynamic_cast<Function*>(actual));

		else if (auto variable = dynamic_cast<Variable*>(expected))
			assertEqualVariable(variable, dynamic_cast<Variable*>(expected));

		else
			EXPECT_EQ_STR(expected->verbatim(), actual->verbatim());
	}
}