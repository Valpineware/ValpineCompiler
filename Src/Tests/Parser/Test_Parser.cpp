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
	void assertValpineToGraphScript(const QString &valpineFile, const QString &parseScriptFile)
	{
		parser::Parser sp;
		ASSERT_TRUE(sp.parseFile(gTestDir_Parser + valpineFile)) << "Does the valpine file exist?";

		GraphScript parseScript;
		ASSERT_TRUE(parseScript.parse(gTestDir_Parser + parseScriptFile)) << "Does the GS file exist?";

		assertEqualBlock(parseScript.graph().block(), sp.graph().block());
	}
};


TEST_CASE(HelloWorld)
{
	assertValpineToGraphScript("HelloWorld.val", "HelloWorld.gs");
}


TEST_CASE(FunctionSignature)
{
	assertValpineToGraphScript("Function.val", "Function.gs");
}


TEST_CASE(ControlStructure)
{
	assertValpineToGraphScript("ControlStructure.val", "ControlStructure.gs");
}


TEST_CASE(Class)
{
	assertValpineToGraphScript("Class.val", "Class.gs");
}


TEST_CASE(Blocks)
{
	assertValpineToGraphScript("Blocks.val", "Blocks.gs");
}