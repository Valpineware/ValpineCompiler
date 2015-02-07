#include "Tests.h"
#include <Parser\Parser.h>
#include <Mocker\Mocker.h>

#define CLASS Test_Mocker
using namespace vc;

const QString gTestDir_Mocker = gTestDir + "/Test_Mocker/";

TEST_CLASS
{
};

TEST_CASE(HelloWorld)
{
	parser::Parser sp;
	sp.parseFile(gTestDir_Mocker + "HelloWorld.val");

	using namespace graph;
	using namespace mocker;

	/*Mocker mocker;
	mocker.mock(sp.graph(), "./");

	QVector<QString> strings = mocker.buildList();

	ASSERT_EQ("#include <iostream>", strings[0]);
	ASSERT_EQ("int main()", strings[1]);
	ASSERT_EQ("{", strings[2]);
	ASSERT_EQ("std::cout << \"HelloWorld\" << std::endl;", strings[3]);
	ASSERT_EQ("return  0;", strings[4]);
	ASSERT_EQ("}", strings[5]);

	ASSERT_EQ(6, strings.size());*/
}