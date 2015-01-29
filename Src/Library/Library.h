#ifndef LIBRARY_H
#define LIBRARY_H

#include <QtCore/QDebug>
#include <QtCore/QDir>

class Library
{
public:
	Library();

    static int add(int a, int b);
    static int divide(int a, int b);
};

#endif // LIBRARY_H
