#include <QCoreApplication>
#include <Library.h>

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

	printf("10+4=%i\n", Library::add(10,4));
	printf("12/2=%i\n", Library::divide(12,2));

	return a.exec();
}
