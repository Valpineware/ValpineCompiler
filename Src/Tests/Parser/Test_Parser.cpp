#include "Tests.h"
#include ".Ext/Graph.h"
#include <Parser/Parser.h>

#define CLASS Test_Parser
using namespace vc;
using namespace ext;

const QString gTestDir_Parser = gTestDir + "/Test_Parser/";

TEST_CLASS
{
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
	parser::Parser sp;
	sp.parseFile(gTestDir_Parser + "ControlStructure.val");

	using namespace graph;

	Block expected;
	{
		addPreprocessor(expected, new Preprocessor("#include <QtCore/QDebug>"));
		auto fMain = addFunction(expected, Function::make("int main()", ScopeType::Root));
			auto csFor = addControlStructure(fMain->block(), ControlStructure::make("for (int i=0; i<100; i++)"));
				addStatement(csFor->block(), new Statement("qDebug() << i;"));

			addVariable(fMain->block(), Variable::make("bool quit = false"));
			addVariable(fMain->block(), Variable::make("int n = 0"));

			auto csWhile = addControlStructure(fMain->block(), ControlStructure::make("while (!quit)"));
				addStatement(csWhile->block(), new Statement("QThread::msleep(100)"));
				addStatement(csWhile->block(), new Statement("n += 40"));
				addStatement(csWhile->block(), new Statement("quit = n>50000"));

			addVariable(fMain->block(), Variable::make("QString username = ""DanWatkins"""));

			auto csIf = addControlStructure(fMain->block(), ControlStructure::make("if (username == ""JohnKoehn"")"));
				addStatement(csIf->block(), new Statement("qDebug() << 56"));

			auto csElseIf = addControlStructure(fMain->block(), ControlStructure::make("elseif (username == ""Noob"" && false)"));
				auto csSubWhile = addControlStructure(csElseIf->block(), ControlStructure::make("while (true)"));
					addStatement(csSubWhile->block(), new Statement("qDebug() << ""Stuck in a loop that will never execute"""));

			auto csElse = addControlStructure(fMain->block(), ControlStructure::make("else"));
				addStatement(csElse->block(), new Statement("qDebug() << ""You must be Dan"""));
	}

	assertEqualBlock(expected, sp.graph().block());
}


TEST_CASE(Class)
{
	parser::Parser sp;
	sp.parseFile(gTestDir_Parser + "Class.val");

	using namespace graph;

	Block &root = sp.graph().block();
	ASSERT_EQ(3, root.statements().count());
	{
		QListIterator<Statement*> iter(root.statements());

		auto include = dynamic_cast<Preprocessor*>(iter.next());
		ASSERT_NOT_NULL(include);
		EXPECT_EQ_STR("#include <QtCore/QDebug>", include->verbatim());

		auto cls = dynamic_cast<Class*>(iter.next());
		ASSERT_NOT_NULL(cls);
		EXPECT_EQ_STR("Book", cls->id());
		{
			QListIterator<Class::Member*> clsIter(cls->members());
			ASSERT_EQ(5, cls->members().count());

			{
				const Class::Member *m = clsIter.next();
				EXPECT_EQ(Class::Public, m->accessType);
				auto f = dynamic_cast<Function*>(m->statement);
				ASSERT_NOT_NULL(f);
				EXPECT_EQ_STR("Book", f->id());
				EXPECT_EQ(Function::Type::Constructor, f->type());
			}

			{
				const Class::Member *m = clsIter.next();
				EXPECT_EQ(Class::Public, m->accessType);
				auto f = dynamic_cast<Function*>(m->statement);
				ASSERT_NOT_NULL(f);
				EXPECT_EQ_STR("Book", f->id());
				EXPECT_EQ(Function::Type::Destructor, f->type());
			}

			{
				const Class::Member *m = clsIter.next();
				EXPECT_EQ(Class::Public, m->accessType);
				auto f = dynamic_cast<Function*>(m->statement);
				ASSERT_NOT_NULL(f);
				EXPECT_EQ_STR("setText", f->id());
				EXPECT_EQ(Function::Type::Normal, f->type());
			}

			
			{
				const Class::Member *m = clsIter.next();
				EXPECT_EQ(Class::Public, m->accessType);
				auto f = dynamic_cast<Function*>(m->statement);
				ASSERT_NOT_NULL(f);
				EXPECT_EQ_STR("read", f->id());
				EXPECT_EQ(Function::Type::Normal, f->type());
			}


			{
				const Class::Member *m = clsIter.next();
				EXPECT_EQ(Class::Private, m->accessType);
				auto v = dynamic_cast<Variable*>(m->statement);
				ASSERT_NOT_NULL(v);
				EXPECT_EQ_STR("QString", v->typeExpression().fullType());
				EXPECT_EQ_STR("mText", v->id());
			}
		}
	}
}