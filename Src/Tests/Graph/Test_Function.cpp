#include "Tests.h"
#include ".Ext/Graph.h"

#define CLASS Test_Function

TEST_CLASS
{
protected:
	void assertInitializerList(const QString start, const QString listBody, int listCount)
	{
		auto f = Function::make(start, ScopeType::ClassBlock);
		Assert::NotNull(f);
		Assert::Eq(f->type(), Function::Type::Constructor);

		auto& initList = f->initializerList();
		Assert::Eq(listCount, initList.components().count());
		std::unique_ptr<Expression::Arguments> expected(Expression::Arguments::make(listBody));
		ext::assertEqualComponentList(expected->components(), initList.components());
	}
};


TEST_CASE(Normal_WhatIS)
{
	//TODO we need to test Function::Type in this test
	#define tst(what) { auto f = Function::make(what, ScopeType::Root); \
						Assert::NotNull(f); \
						Assert::Eq(f->type(), Function::Type::Normal); }

	tst("void simple()")
	tst("int		 wacky	( ) ");
	tst(" bool	isCool(  )");
	tst("		float __compilerFunction ()");
	tst("		double whatIsPi(		)");

	tst(" int* pointer1()");
	tst(" *** void ** crazyPointerThatWontActuallyCompileButShouldLookLikeAFunction()");
	tst("const double& cosntRefPlease()");
	tst("	const void		* const *	const	*& superLongPointerRefThing()");

	tst("QString what()");
	tst("const __MyWeirdTyPe_________ *** _function_Name_Is_Here ( )");

	tst("void singleParameter(int p1)");
	tst("void defaultParameter(int count=12)");
	tst("float multipleDefaultParameters(int mag=10000, int size=147)");
	tst("BigBoolean multipleDefaultParameters(int mag=10000, int size=147)");
	tst("double someDefaultParameters(int a, float m, int size=50)");

	#undef tst
}


TEST_CASE(Constructor_WhatIs)
{
#define tst(what) { auto f = Function::make(what, ScopeType::ClassBlock); \
						Assert::NotNull(f); \
						Assert::Eq(f->type(), Function::Type::Constructor); }

	tst("Widget()");
	tst("Widget(const Widget &widget)");
	tst("my_type(const QString &name, int size)");

#undef tst
}


TEST_CASE(Constructor_InitiailzerList_OneArgument)
{
	assertInitializerList("Cow() : mSize(140)", "mSize(140)", 1);
}


TEST_CASE(Constructor_InitiailzerList_TwoArgument)
{
	assertInitializerList("Entity():mRenderable(new Renderable(300)),mRadius(4.7)", "mRenderable(new Renderable(300)), mRadius(4.7)", 2);
}


TEST_CASE(Destructor_WhatIs)
{
#define tst(what) { auto f = Function::make(what, ScopeType::ClassBlock); \
					Assert::NotNull(f); \
					Assert::Eq(f->type(), Function::Type::Destructor); }

	tst("~Widget()");
	tst("  ~ BigWidget ( )");
	tst("~ destructorWithParameter(int parameter)") //this should be considered a dtor, but should generate an error later

#undef tst
}


TEST_CASE(Normal_WhatIsNot)
{
#define tst(what) Assert::Null(Function::make(what, ScopeType::Root))

	tst("123Type doesNotWork()");
	tst("NoGo 999Function		( )");
	tst("Don't useWeirdSybols()");
	tst("Ever !()");

	tst("float Not A Function()");
	tst("float functionDeclarationsDontExistInValpine() ;");

	tst("float thisIsImpossible(int a==3254, int m=  =	9832)");
	tst("return &(new bool);");

#undef tst
}


TEST_CASE(Constructor_WhatIsNot)
{
#define tst(what) Assert::Null(Function::make(what, ScopeType::ClassBlock))
    tst("Barnicle() mCount(400)");
#undef tst
}


TEST_CASE(Destructor_WhatIsNot)
{
#define tst(what, scope) Assert::Null(Function::make(what, ScopeType::scope))

	//can't have destructors and constructors in regular scopes
	//TODO should we still consider these constructors and destructors just for the sake of error checking?
	tst("~Widget()", Root);
	tst("~ Bigger_Widget( )", ExecutionBlock);

#undef tst
}