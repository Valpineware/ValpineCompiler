#include <QtCore/QBuffer>

#include <Parser/Parser.h>
#include <Mocker/Mocker.h>

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
		Assert::True(buffer.open(QIODevice::ReadWrite | QIODevice::Text));
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


	void readFile(const QString& filename, QVector<QString>& lines)
	{
		QFile file(gTestDir_Mocker + filename);
		Assert::True(file.open(QFile::ReadOnly | QFile::Text));
		QTextStream in(&file);
		
		while (!in.atEnd())
		{
			lines.append(in.readLine());
		}
	}
};


//TODO Hey John. All these test cases duplicate a lot of code. Bi.
TEST_CASE(HelloWorld)
{
	QVector<QString> lines;
	readLines("HelloWorld.val", lines);

	QVector<QString> expected;
	readFile("HelloWorld.cpp", expected);

	Assert::Eq(expected.size(), lines.size());

	for (int i = 0; i < expected.size(); i++)
	{
		Expect::EqStr(expected[i], lines[i]);
	}
}

TEST_CASE(FunctionTest)
{
	QVector<QString> lines;
	readLines("FunctionTest.val", lines);

	QVector<QString> expected;
	readFile("FunctionTest.cpp", expected);

	Assert::Eq(expected.size(), lines.size());

	for (int i = 0; i < expected.size(); i++)
	{
		Expect::EqStr(expected[i], lines[i]);
	}
}

TEST_CASE(VariableTest)
{
	QVector<QString> lines;
	readLines("VariableTest.val", lines);

	QVector<QString> expected;
	readFile("VariableTest.cpp", expected);

	Assert::Eq(expected.size(), lines.size());

	for (int i = 0; i < expected.size(); i++)
	{
		Expect::EqStr(expected[i], lines[i]);
	}
}


TEST_CASE(NestedFunctionBasic)
{
	QVector<QString> lines;
	readLines("NestedFunctionBasic.val", lines);

	QVector<QString> expected;
	readFile("NestedFunctionBasic.cpp", expected);

	Assert::Eq(expected.size(), lines.size());
	
	for (int i = 0; i < expected.size(); i++)
	{
		Expect::EqStr(expected[i], lines[i]);
	}

}

TEST_CASE(ConditionalStatements)
{
	QVector<QString> lines;
	readLines("ConditionalStatementsBasic.val", lines);

	QVector<QString> expected;
	readFile("ConditionalStatementsBasic.cpp", expected);

	Assert::Eq(expected.size(), lines.size());

	for (int i = 0; i < expected.size(); i++)
	{
		Expect::EqStr(expected[i], lines[i]);
	}
}