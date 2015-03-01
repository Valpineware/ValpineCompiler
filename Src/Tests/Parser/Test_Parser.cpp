#include "Tests.h"
#include ".Ext/Graph.h"
#include ".Ext/GraphScript.h"
#include <Parser/Parser.h>

#define CLASS Test_Parser
using namespace vc;
using namespace ext;

const QString gTestDir_Parser = gTestDir + "/Test_Parser/";

TEST_CLASS
{
protected:
	void assertValpineToParseScript(const QString &valpineFile, const QString &parseScriptFile)
	{
		parser::Parser sp;
		sp.parseFile(gTestDir_Parser + valpineFile);

		GraphScript parseScript;
		parseScript.parse(gTestDir_Parser + parseScriptFile);

		assertEqualBlock(parseScript.graph().block(), sp.graph().block());
	}
};


TEST_CASE(HelloWorld)
{
	parser::Parser sp;
	sp.parseFile(gTestDir_Parser + "HelloWorld.val");

	using namespace graph;

	Block &root = sp.graph().block();
	ASSERT_EQ(2, root.statements().count());
	{
		Preprocessor *include = dynamic_cast<Preprocessor*>(root.statements().first());
		ASSERT_NOT_NULL(include);
		EXPECT_EQ_STR("#include <iostream>", include->verbatim());
	
		Function *main = dynamic_cast<Function*>(root.statements().last());
		ASSERT_NOT_NULL(main);
		EXPECT_EQ_STR("int main()", main->verbatim());
		ASSERT_EQ(2, main->block().statements().count());
		{
			EXPECT_EQ_STR("std::cout << \"HelloWorld\" << std::endl;", main->block().statements().first()->verbatim());
			EXPECT_EQ_STR("return  0;", main->block().statements().last()->verbatim());
		}
	}
}


TEST_CASE(Function)
{
	parser::Parser sp;
	sp.parseFile(gTestDir_Parser + "Function.val");

	using namespace graph;

	Block &root = sp.graph().block();
	ASSERT_EQ(3, root.statements().count());
	{
		QListIterator<Statement*> iter(root.statements());

		Preprocessor *include = dynamic_cast<Preprocessor*>(iter.next());
		ASSERT_NOT_NULL(include);
		EXPECT_EQ_STR("#include <iostream>", include->verbatim());

		Function *main = dynamic_cast<Function*>(iter.next());
		ASSERT_NOT_NULL(main);
		EXPECT_EQ_STR("int main()", main->verbatim());
		ASSERT_EQ(2, main->block().statements().count());
		{
			QListIterator<Statement*> iter(main->block().statements());
			EXPECT_EQ_STR("foo();", iter.next()->verbatim());
			EXPECT_EQ_STR("return 0;", iter.next()->verbatim());
		}

		Function *foo = dynamic_cast<Function*>(iter.next());
		ASSERT_NOT_NULL(foo);
		EXPECT_EQ_STR("void foo()", foo->verbatim());
		ASSERT_EQ(1, foo->block().statements().count());
		{
			QListIterator<Statement*> iter(foo->block().statements());
			EXPECT_EQ_STR("std::cout << \"Called foo\" << std::endl;", iter.next()->verbatim());
		}
	}
}


TEST_CASE(FunctionSignature)
{
	parser::Parser sp;
	sp.parseFile(gTestDir_Parser + "FunctionSignature.val");

	using namespace graph;

	Block &root = sp.graph().block();
	ASSERT_EQ(3, root.statements().count());
	{
		QListIterator<Statement*> iter(root.statements());

		Function *f1 = dynamic_cast<Function*>(iter.next());
		ASSERT_NOT_NULL(f1);
		EXPECT_EQ_STR("access", f1->id());
		{
			graph::TypeExpression te = f1->returnType();
			EXPECT_EQ_STR("int", te.baseType());
			EXPECT_EQ_STR("*", te.postModifiers()[0]);
			{
				QVector<Parameter> prms = f1->parameters();
				ASSERT_EQ(2,prms.count());
				EXPECT_EQ_STR("bool", prms[0].type.baseType());
				EXPECT_EQ_STR("opened", prms[0].id);
				EXPECT_EQ_STR("int", prms[1].type.baseType());
				EXPECT_EQ_STR("count", prms[1].id);
			}
		}


		Function *f2 = dynamic_cast<Function*>(iter.next());
		ASSERT_NOT_NULL(f2);
		EXPECT_EQ_STR("apply", f2->id());
		{
			graph::TypeExpression te = f2->returnType();
			EXPECT_EQ_STR("void", te.baseType());
			{
				QVector<Parameter> prms = f2->parameters();
				ASSERT_EQ(1,prms.count());
				EXPECT_EQ_STR("float", prms[0].type.baseType());
				EXPECT_EQ_STR("amount", prms[0].id);
				EXPECT_EQ_STR("14.0f", prms[0].defaultValue);

			}
		}


		Function *f3 = dynamic_cast<Function*>(iter.next());
		ASSERT_NOT_NULL(f3);
		EXPECT_EQ_STR("longDistanceCommunication", f3->id());
		{
			graph::TypeExpression te = f3->returnType();
			EXPECT_EQ_STR("bool", te.baseType());
			EXPECT_EQ_STR("*", te.postModifiers()[0]);
			EXPECT_EQ_STR("*", te.postModifiers()[1]);
			{
				QVector<Parameter> prms = f3->parameters();
				ASSERT_EQ(3,prms.count());
				EXPECT_EQ_STR("Type1", prms[0].type.baseType());
				EXPECT_EQ_STR("t1", prms[0].id);
				
				EXPECT_EQ_STR("Type2", prms[1].type.baseType());
				EXPECT_EQ_STR("t2", prms[1].id);
				
				EXPECT_EQ_STR("float", prms[2].type.baseType());
				EXPECT_EQ_STR("distance", prms[2].id);
				EXPECT_EQ_STR("320.0f", prms[2].defaultValue);
			}
		}
	}
}


TEST_CASE(ControlStructure)
{
	assertValpineToParseScript("ControlStructure.val", "ControlStructure.gs");
}


TEST_CASE(Class)
{
	assertValpineToParseScript("Class.val", "Class.gs");
}