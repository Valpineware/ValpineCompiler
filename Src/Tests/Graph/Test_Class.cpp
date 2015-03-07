#include "Tests.h"
#include <Graph/Class.h>

#define CLASS Test_Class
using namespace vc::graph;

TEST_CLASS
{
};


TEST_CASE(FunctionHeader_WhatIs)
{
	#define IF(what) { Class *c = Class::make(what); ASSERT_NOT_NULL(c);

	IF ("class Cow : public Animal")
		EXPECT_EQ_STR("Cow", c->id());

		ASSERT_EQ(1, c->superClasses().count());
		EXPECT_EQ_STR("Animal", c->superClasses().first().id);
		EXPECT_EQ(Class::Public, c->superClasses().first().accessType);
	}

	IF ("class Door : public Entity, protected Openable")
		EXPECT_EQ_STR("Door", c->id());

		ASSERT_EQ(2, c->superClasses().count());
		EXPECT_EQ_STR("Entity", c->superClasses().first().id);
		EXPECT_EQ(Class::Public, c->superClasses().first().accessType);
		EXPECT_EQ_STR("Openable", c->superClasses().last().id);
		EXPECT_EQ(Class::Protected, c->superClasses().last().accessType);
	}

	IF ("class Door : public Entity <private Openable>")
		EXPECT_EQ_STR("Door", c->id());

		ASSERT_EQ(1, c->superClasses().count());
		EXPECT_EQ_STR("Entity", c->superClasses().first().id);
		EXPECT_EQ(Class::Public, c->superClasses().first().accessType);

		ASSERT_EQ(1, c->interfaces().count());
		EXPECT_EQ_STR("Openable", c->interfaces().last().id);
		EXPECT_EQ(Class::Private, c->interfaces().last().accessType);
	}

	IF ("class Book <public Readable>")
		EXPECT_EQ_STR("Book", c->id());
		ASSERT_EQ(0, c->superClasses().count());
		ASSERT_EQ(1, c->interfaces().count());
		EXPECT_EQ_STR("Readable", c->interfaces().last().id);
		EXPECT_EQ(Class::Public, c->interfaces().last().accessType);
	}

	#undef IF
}


TEST_CASE(FunctionHeader_WhatIsNot)
{
	const QString header = "void process()";

	#define tst(what) ASSERT_NULL(Class::make(what))

	tst("class Door :: public Entity");

	#undef tst
}