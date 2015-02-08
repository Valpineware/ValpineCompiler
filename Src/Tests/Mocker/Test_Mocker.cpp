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
		bool success = buffer.open(QIODevice::ReadWrite | QIODevice::Text);
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

	ASSERT_EQ("#include <iostream>", lines[0]);
	ASSERT_EQ("int main()", lines[1]);
	ASSERT_EQ("{", lines[2]);
	ASSERT_EQ("std::cout << \"HelloWorld\" << std::endl;", lines[3]);
	ASSERT_EQ("return  0;", lines[4]);
	ASSERT_EQ("}", lines[5]);
}