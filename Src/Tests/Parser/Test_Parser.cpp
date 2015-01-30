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
	sp.parseFile(gTestDir + "HelloWorld.val");

	using namespace graph;

	Block &root = sp.graph().block();
	ASSERT_EQ(2, root.statements().count());

	Preprocessor *include = dynamic_cast<Preprocessor*>(root.statements().first());
	ASSERT_NOT_NULL(include);
	ASSERT_EQ("#include <iostream>", include->verbatim());
	
	Function *main = dynamic_cast<Function*>(root.statements().last());
	ASSERT_NOT_NULL(main) << "Second statement is not int main()";
	ASSERT_EQ(main->verbatim(), "int main()");

	ASSERT_EQ(2, main->block().statements().count());

	ASSERT_EQ(QString("std::cout << \"HelloWorld\" << std::endl;"), main->block().statements().first()->verbatim());
	ASSERT_EQ(QString("return 0;"), main->block().statements().last()->verbatim());
}