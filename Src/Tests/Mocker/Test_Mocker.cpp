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

		QBuffer bufferImplementation;
		ASSERT_TRUE(bufferImplementation.open(QIODevice::ReadWrite | QIODevice::Text));
		QBuffer bufferHeader;
		ASSERT_TRUE(bufferHeader.open(QIODevice::ReadWrite | QIODevice::Text));

		mocker::Mocker().mock(parser.graph(), bufferImplementation, bufferHeader);


		QTextStream stream(&bufferImplementation.buffer());
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
		ASSERT_TRUE(file.open(QFile::ReadOnly | QFile::Text));
		QTextStream in(&file);
		
		while (!in.atEnd())
		{
			lines.append(in.readLine());
		}
	}

	void performTest(QString valpineFile, QString cppFile)
	{
		QVector<QString> lines;
		readLines(valpineFile, lines);

		QVector<QString> expected;
		readFile(cppFile, expected);

		ASSERT_EQ(expected.size(), lines.size());

		for (int i = 0; i < expected.size(); i++)
		{
			EXPECT_EQ_STR(expected[i], lines[i]);
		}
	}


};


//TODO Hey John. All these test cases duplicate a lot of code. Bi. 
//Okay, BI.
TEST_CASE(HelloWorld)
{
	performTest("HelloWorld.val", "HelloWorld.cpp");
}

TEST_CASE(FunctionTest)
{
	performTest("FunctionTest.val", "FunctionTest.cpp");
}

TEST_CASE(VariableTest)
{
	performTest("VariableTest.val", "VariableTest.cpp");
}


TEST_CASE(NestedFunctionBasic)
{
	performTest("NestedFunctionBasic.val", "NestedFunctionBasic.cpp");

}

TEST_CASE(ConditionalStatements)
{
	performTest("ConditionalStatementsBasic.val", "ConditionalStatementsBasic.cpp");
}