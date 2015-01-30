#include "Tests.h"
#include <Parser/Parser.h>

#define CLASS Test_Parser
using namespace vc;

TEST_CLASS
{
};



TEST_CASE(HelloWorld)
{
	parser::Parser sp;
	sp.parseFile(gTestDir + "/HelloWorld/HelloWorld.val");

	using namespace graph;

	Block &root = sp.graph().block();
	ASSERT_EQ(2, root.statements().count());
	{
		Preprocessor *include = dynamic_cast<Preprocessor*>(root.statements().first());
		ASSERT_NOT_NULL(include);
		ASSERT_EQ("#include <iostream>", include->verbatim());
	
		Function *main = dynamic_cast<Function*>(root.statements().last());
		ASSERT_NOT_NULL(main);
		ASSERT_EQ("int main()", main->verbatim());
		ASSERT_EQ(2, main->block().statements().count());
		{
			ASSERT_EQ(QString("std::cout << \"HelloWorld\" << std::endl;"), main->block().statements().first()->verbatim());
			ASSERT_EQ(QString("return 0;"), main->block().statements().last()->verbatim());
		}
	}
}


TEST_CASE(Function)
{
	parser::Parser sp;
	sp.parseFile(gTestDir + "/Function/Function.val");

	using namespace graph;

	Block &root = sp.graph().block();
	ASSERT_EQ(3, root.statements().count());
	{
		QListIterator<Statement*> iter(root.statements());

		Preprocessor *include = dynamic_cast<Preprocessor*>(iter.next());
		ASSERT_NOT_NULL(include);
		ASSERT_EQ("#include <iostream>", include->verbatim());

		Function *main = dynamic_cast<Function*>(iter.next());
		ASSERT_NOT_NULL(main);
		ASSERT_EQ("int main()", main->verbatim());
		ASSERT_EQ(2, main->block().statements().count());
		{
			QListIterator<Statement*> iter(main->block().statements());
			ASSERT_EQ("foo();", iter.next()->verbatim());
			ASSERT_EQ("return 0;", iter.next()->verbatim());
		}

		Function *foo = dynamic_cast<Function*>(iter.next());
		ASSERT_NOT_NULL(foo);
		ASSERT_EQ("void foo()", foo->verbatim());
		ASSERT_EQ(1, foo->block().statements().count());
		{
			QListIterator<Statement*> iter(foo->block().statements());
			ASSERT_EQ("std::cout << \"Called foo\" << std::endl;", iter.next()->verbatim());
		}
	}
}