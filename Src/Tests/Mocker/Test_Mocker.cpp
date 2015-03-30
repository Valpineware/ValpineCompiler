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
	void readLines(const QString& filename, QVector<QString>& cppData, QVector<QString>& headerData)
	{
		parser::Parser parser;
		parser.parseFile(gTestDir_Mocker + filename);

		QBuffer bufferImplementation;
		ASSERT_TRUE(bufferImplementation.open(QIODevice::ReadWrite | QIODevice::Text));
		QBuffer bufferHeader;
		ASSERT_TRUE(bufferHeader.open(QIODevice::ReadWrite | QIODevice::Text));

		mocker::Mocker().mock(parser.graph(), bufferImplementation, bufferHeader);

		readBuffer(bufferImplementation, cppData);
		readBuffer(bufferHeader, headerData);
	}

	void readBuffer(QBuffer &buffer, QVector<QString> &lines)
	{
		QTextStream stream(&buffer.buffer());

		do
		{
			QString line = stream.readLine();
			if (line != "\n")
			{
				lines.append(line);
			}
			
		} while (!lines.last().isNull());

		if (!lines.isEmpty() && lines.last().isNull())
			lines.removeLast();

	}

	void readFile(const QString& filename, QVector<QString>& lines)
	{
		QFile file(gTestDir_Mocker + filename);
		ASSERT_TRUE(file.open(QFile::ReadOnly | QFile::Text));
		QTextStream in(&file);
		
		while (!in.atEnd())
		{
			QString line = in.readLine();
			if (line != "\n")
			{
				lines.append(line);
			}
		}
	}

	void performTest(QString valpineFile, QString cppFile, QString headerFile)
	{
		//mock the valpine file and get the mocker "output"
		QVector<QString> cppLines;
		QVector<QString> headerLines;
		readLines(valpineFile, cppLines, headerLines);

		//get the expected data
		QVector<QString> cppExpected;
		QVector<QString> headerExpected;
		readFile(cppFile, cppExpected);
		readFile(headerFile, headerExpected);

		ASSERT_EQ(cppExpected.size(), cppLines.size());

		for (int i = 0; i < cppExpected.size(); i++)
		{
			EXPECT_EQ_STR(cppExpected[i], cppLines[i]);
		}

		ASSERT_EQ(headerExpected.size(), headerLines.size());

		for (int i = 0; i < headerExpected.size(); i++)
		{
			EXPECT_EQ_STR(headerExpected[i], headerLines[i]);
		}
	}


};


//TODO Hey John. All these test cases duplicate a lot of code. Bi. 
//Okay, BI.
TEST_CASE(HelloWorld)
{
	performTest("HelloWorld.val", "HelloWorld.cpp", "HelloWorld.h");
}

TEST_CASE(FunctionTest)
{
	performTest("FunctionTest.val", "FunctionTest.cpp", "FunctionTest.h");
}

TEST_CASE(VariableTest)
{
	performTest("VariableTest.val", "VariableTest.cpp", "VariableTest.h");
}


TEST_CASE(NestedFunctionBasic)
{
	performTest("NestedFunctionBasic.val", "NestedFunctionBasic.cpp", "NestedFunctionBasic.h");

}

TEST_CASE(ConditionalStatements)
{
	performTest("ConditionalStatementsBasic.val", "ConditionalStatementsBasic.cpp", "ConditionalStatementsBasic.h");
}