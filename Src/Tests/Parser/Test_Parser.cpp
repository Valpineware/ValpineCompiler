#include "Tests.h"
#include <Parser/Parser.h>

#define CLASS Test_Parser
using namespace vc;

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
		ASSERT_EQ("#include <iostream>", include->verbatim());
	
		Function *main = dynamic_cast<Function*>(root.statements().last());
		ASSERT_NOT_NULL(main);
		ASSERT_EQ("int main()", main->verbatim());
		ASSERT_EQ(2, main->block().statements().count());
		{
			ASSERT_EQ("std::cout << \"HelloWorld\" << std::endl;", main->block().statements().first()->verbatim());
			ASSERT_EQ("return  0;", main->block().statements().last()->verbatim());
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
		EXPECT_EQ("access", f1->id());
		{
			graph::TypeExpression te = f1->returnType();
			EXPECT_EQ("int", te.baseType());
			EXPECT_EQ("*", te.postModifiers()[0]);
			{
				QVector<Parameter> prms = f1->parameters();
				ASSERT_EQ(2,prms.count());
				EXPECT_EQ("bool", prms[0].type.baseType());
				EXPECT_EQ("opened", prms[0].id);
				EXPECT_EQ("int", prms[1].type.baseType());
				EXPECT_EQ("count", prms[1].id);
			}
		}


		Function *f2 = dynamic_cast<Function*>(iter.next());
		ASSERT_NOT_NULL(f2);
		EXPECT_EQ("apply", f2->id());
		{
			graph::TypeExpression te = f2->returnType();
			EXPECT_EQ("void", te.baseType());
			{
				QVector<Parameter> prms = f2->parameters();
				ASSERT_EQ(1,prms.count());
				EXPECT_EQ("float", prms[0].type.baseType());
				EXPECT_EQ("amount", prms[0].id);
				EXPECT_EQ("14.0f", prms[0].defaultValue);

			}
		}


		Function *f3 = dynamic_cast<Function*>(iter.next());
		ASSERT_NOT_NULL(f3);
		EXPECT_EQ("longDistanceCommunication", f3->id());
		{
			graph::TypeExpression te = f3->returnType();
			EXPECT_EQ("bool", te.baseType());
			EXPECT_EQ("*", te.postModifiers()[0]);
			EXPECT_EQ("*", te.postModifiers()[1]);
			{
				QVector<Parameter> prms = f3->parameters();
				ASSERT_EQ(3,prms.count());
				EXPECT_EQ("Type1", prms[0].type.baseType());
				EXPECT_EQ("t1", prms[0].id);
				
				EXPECT_EQ("Type2", prms[1].type.baseType());
				EXPECT_EQ("t2", prms[1].id);
				
				EXPECT_EQ("float", prms[2].type.baseType());
				EXPECT_EQ("distance", prms[2].id);
				EXPECT_EQ("320.0f", prms[2].defaultValue);
			}
		}
	}
}


TEST_CASE(ControlStructure)
{
	parser::Parser sp;
	sp.parseFile(gTestDir_Parser + "ControlStructure.val");

	using namespace graph;

	Block &root = sp.graph().block();
	ASSERT_EQ(2, root.statements().count());
	{
		QListIterator<Statement*> iter(root.statements());

		Preprocessor *include = dynamic_cast<Preprocessor*>(iter.next());
		ASSERT_NOT_NULL(include);
		EXPECT_EQ("#include <QtCore/QDebug>", include->verbatim());

		Function *f1 = dynamic_cast<Function*>(iter.next());
		ASSERT_NOT_NULL(f1);
		EXPECT_EQ("main", f1->id());
		{
			QListIterator<Statement*> f1Iter(f1->block().statements());

			ControlStructure *csFor = dynamic_cast<ControlStructure*>(f1Iter.next());
			ASSERT_NOT_NULL(csFor);
			EXPECT_EQ("for", csFor->name());
			EXPECT_EQ("int i=0; i<100; i++", csFor->expression());
			{
				EXPECT_EQ("qDebug() << i;", csFor->block().statements().first()->verbatim());
			}

			EXPECT_EQ("bool quit = false;", f1Iter.next()->verbatim());
			EXPECT_EQ("int n = 0;", f1Iter.next()->verbatim());

			ControlStructure *csWhile = dynamic_cast<ControlStructure*>(f1Iter.next());
			ASSERT_NOT_NULL(csWhile);
			EXPECT_EQ("while", csWhile->name());
			EXPECT_EQ("!quit", csWhile->expression());
			{
				QListIterator<Statement*> csWhileIter(csWhile->block().statements());

				EXPECT_EQ("QThread::msleep(100);", csWhileIter.next()->verbatim());
				EXPECT_EQ("n += 40;", csWhileIter.next()->verbatim());
				EXPECT_EQ("agsdg	quit = n>50000;", csWhileIter.next()->verbatim());
			}
		}

		//TODO finish testing rest of the file
	}
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

		Preprocessor *include = dynamic_cast<Preprocessor*>(iter.next());
		ASSERT_NOT_NULL(include);
		EXPECT_EQ("#include <QtCore/QDebug>", include->verbatim());

		Class *cls = dynamic_cast<Class*>(iter.next());
		ASSERT_NOT_NULL(cls);
		EXPECT_EQ("Book", cls->id());
		{
			QListIterator<Class::Member*> clsIter(cls->members());

			{
				const Class::Member *m = clsIter.next();
				EXPECT_EQ(Class::Public, m->accessType);
				Function *f = dynamic_cast<Function*>(m->statement);
				ASSERT_NOT_NULL(f);
				EXPECT_EQ("setText", f->id());
			}

			
			{
				const Class::Member *m = clsIter.next();
				EXPECT_EQ(Class::Public, m->accessType);
				Function *f = dynamic_cast<Function*>(m->statement);
				ASSERT_NOT_NULL(f);
				EXPECT_EQ("read", f->id());
			}


			{
				const Class::Member *m = clsIter.next();
				EXPECT_EQ(Class::Private, m->accessType);
				Variable *v = dynamic_cast<Variable*>(m->statement);
				ASSERT_NOT_NULL(v);
				EXPECT_EQ("QString", v->typeExpression().fullType());
				EXPECT_EQ("mText", v->id());
			}
		}
	}
}