//==================================================================================================================|
// Created 2015.01.28 by Daniel L. Watkins
//
// Copyright (C) 2015 Valpineware
// This file is licensed under the MIT License.
//==================================================================================================================|

#include <QGuiApplication>

#include <Application.h>
#include <Parser/Recognizer.h>


int main(int argc, char *argv[])
{
	QGuiApplication a(argc, argv);

	if (vc::parser::Recognizer::isFunctionHeader("void "))
		qDebug() << "Looks like a function header!";

	Application application;
	application.init();
	application.show();

	return a.exec();
}