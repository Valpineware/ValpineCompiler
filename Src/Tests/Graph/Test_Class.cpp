#include "Tests.h"
#include <Graph/Class.h>

#define CLASS Test_Class
using namespace vc::graph;

TEST_CLASS
{
};


TEST_CASE(FunctionHeader_WhatIs)
{
	#define IF(what) { Class *c = Class::createFromVerbatimSignature(what); ASSERT_NOT_NULL(c);

	IF ("class Cow : public Animal")
		EXPECT_EQ_STR("Cow", c->id());

		ASSERT_EQ(1, c->superClasses().count());
		EXPECT_EQ_STR("Animal", c->superClasses().first().id);
		EXPECT_EQ(Class::Public, c->superClasses().first().accessType);
	}	

	#undef IF
}


TEST_CASE(FunctionHeader_WhatIsNot)
{
	const QString header = "void process()";

	#define tst(what) ASSERT_NULL(Class::createFromVerbatimSignature(what))

	tst("class Door :: public Entity");

	#undef tst
}
