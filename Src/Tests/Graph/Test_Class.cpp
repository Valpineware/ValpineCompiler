#include "Tests.h"
#include <Graph/Class.h>

#define CLASS Test_Class
using namespace vc::graph;

TEST_CLASS
{
};


TEST_CASE(FunctionHeader_WhatIs)
{
	#define IF(what) { Class *c = Class::make(what); Assert::NotNull(c);

	IF ("class Cow : public Animal")
		Expect::EqStr("Cow", c->id());

		Assert::Eq(1, c->superClasses().count());
		Expect::EqStr("Animal", c->superClasses().first().id);
		Expect::Eq(Class::Public, c->superClasses().first().accessType);
	}

	IF ("class Door : public Entity, protected Openable")
		Expect::EqStr("Door", c->id());

		Assert::Eq(2, c->superClasses().count());
		Expect::EqStr("Entity", c->superClasses().first().id);
		Expect::Eq(Class::Public, c->superClasses().first().accessType);
		Expect::EqStr("Openable", c->superClasses().last().id);
		Expect::Eq(Class::Protected, c->superClasses().last().accessType);
	}

	IF ("class Door : public Entity <private Openable>")
		Expect::EqStr("Door", c->id());

		Assert::Eq(1, c->superClasses().count());
		Expect::EqStr("Entity", c->superClasses().first().id);
		Expect::Eq(Class::Public, c->superClasses().first().accessType);

		Assert::Eq(1, c->interfaces().count());
		Expect::EqStr("Openable", c->interfaces().last().id);
		Expect::Eq(Class::Private, c->interfaces().last().accessType);
	}

	IF ("class Book <public Readable>")
		Expect::EqStr("Book", c->id());
		Assert::Eq(0, c->superClasses().count());
		Assert::Eq(1, c->interfaces().count());
		Expect::EqStr("Readable", c->interfaces().last().id);
		Expect::Eq(Class::Public, c->interfaces().last().accessType);
	}

	#undef IF
}


TEST_CASE(FunctionHeader_WhatIsNot)
{
	const QString header = "void process()";

	#define tst(what) Assert::Null(Class::make(what))

	tst("class Door :: public Entity");

	#undef tst
}