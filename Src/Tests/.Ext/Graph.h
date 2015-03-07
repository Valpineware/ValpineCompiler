#ifndef _test_ext_Graph_H
#define _test_ext_Graph_H

#include <functional>

#include "../Tests.h"
#include "Expression.h"
#include <Graph/Graph.h>
using namespace vc::graph;

namespace ext
{
	Statement* addStatement(Block &block, Statement *statement);
	Preprocessor* addPreprocessor(Block &block, Preprocessor *preprocessor);
	Class* addClass(Block &block, Class *cls);
	ControlStructure* addControlStructure(Block &block, ControlStructure *controlStructure);
	Expression* addExpression(Block &block,  Expression *expression);
	Function* addFunction(Block &block, Function *function);
	Variable* addVariable(Block &block, Variable *variable);


	void assertEqualBlock(const Block &expected, const Block &actual);
	void assertEqualStatement(Statement *expected, Statement *actual);
	void assertEqualPreprocessor(Preprocessor *expected, Preprocessor *actual);

	template <typename T>
	void assertSameLists(const QList<T> &list1, const QList<T> &list2, std::function<void(const T&, const T&)> assertCompare)
	{
		ASSERT_EQ(list1.count(), list2.count());
		{
			auto expectIter = vc::makeIter(list1);
			auto actualIter = vc::makeIter(list2);

			while (expectIter.hasNext())
			{
				assertCompare(expectIter.next(), actualIter.next());
			}
		}
	}


	void assertEqualClass(Class *expected, Class *actual);
	void assertEqualControlStructure(ControlStructure *expected, ControlStructure *actual);
	void assertEqualFunction(Function *expected, Function *actual);
	void assertEqualVariable(Variable *expected, Variable *actual);
	void assertEqualBlock(const Block &expected, const Block &actual);
	void assertEqualStatement(Statement *expected, Statement *actual);
}

#endif
