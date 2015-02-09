#include <QtCore/QBuffer>

#include <Parser\Parser.h>
#include <Mocker\Mocker.h>

#include "Tests.h"


#define CLASS Test_Mocker
using namespace vc;

const QString gTestDir_Mocker = gTestDir + "/Test_Mocker/";

TEST_CLASS
{
protected:
	void readLines(const QString& filename, QVector<QString>& lineBuffer)
	{
		parser::Parser parser;
		parser.parseFile(gTestDir_Mocker + filename);

		QBuffer buffer;
		ASSERT_TRUE(buffer.open(QIODevice::ReadWrite | QIODevice::Text));
		mocker::Mocker().mock(parser.graph(), buffer);

		QTextStream stream(&buffer.buffer());
		QVector<QString> lines;

		do
		{
			lineBuffer.append(stream.readLine());
		} while (!lineBuffer.last().isNull());

		if (!lineBuffer.isEmpty() && lineBuffer.last().isNull())
			lineBuffer.removeLast();
	}
};


TEST_CASE(HelloWorld)
{
	QVector<QString> lines;
	readLines("HelloWorld.val", lines);

	ASSERT_EQ(6, lines.size());

	EXPECT_EQ_STR("#include <iostream>", lines[0]);
	EXPECT_EQ_STR("int main()", lines[1]);
	EXPECT_EQ_STR("{", lines[2]);
	EXPECT_EQ_STR("std::cout << \"HelloWorld\" << std::endl;", lines[3]);
	EXPECT_EQ_STR("return 0;", lines[4]);
	EXPECT_EQ_STR("}", lines[5]);
}

TEST_CASE(FunctionTest)
{
	QVector<QString> lines;
	readLines("FunctionTest.val", lines);

	ASSERT_EQ(13, lines.size());

	EXPECT_EQ_STR("int * access(bool opened, int count);", lines[0]);
	EXPECT_EQ_STR("int add(int a, int b=5, int c=4);", lines[1]);
	EXPECT_EQ_STR("int * access(bool opened, int count)", lines[2]);
	EXPECT_EQ_STR("{", lines[3]);
	EXPECT_EQ_STR("return new int;", lines[4]);
	EXPECT_EQ_STR("}", lines[5]);
	EXPECT_EQ_STR("int add(int a, int b=5, int c=4)", lines[6]);
}

TEST_CASE(VariableTest)
{
	QVector<QString> lines;
	readLines("VariableTest.val", lines);

	ASSERT_EQ(8, lines.size());
	EXPECT_EQ_STR("int x;", lines[2]);
	EXPECT_EQ_STR("x = 5;", lines[3]);
	EXPECT_EQ_STR("int * y;", lines[4]);
	EXPECT_EQ_STR("int z = x;", lines[5]);
	EXPECT_EQ_STR("y = &x;", lines[6]);
}