#include "Tests.h"

#include <fstream>

void assertEqStr(const QString &exp, const QString &actual, const char *file, int line)
{
	if (exp != actual)
	{
		std::string message = std::string("Value of QString in " + std::string(file) + "(line " + QString::number(line).toStdString() + "):") + "\n" + "Expected: \"" + exp.toStdString() + "\"\n" +
										"Actual: \"" + actual.toStdString() + "\"";
		ADD_FAILURE() << message;
	}
}

int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}