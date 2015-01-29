//==================================================================================================================|
// Created 2015.01.28 by Daniel L. Watkins
//
// Copyright (C) 2015 Valpineware
// This file is licensed under the MIT License.
//==================================================================================================================|

#include <QCoreApplication>

#include <CppCompiler.h>

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

	CppCompiler CppCompiler;
	CppCompiler.run();

	return 0;
}
