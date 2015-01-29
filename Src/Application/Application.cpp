//==================================================================================================================|
// Created 2015.01.29 by Daniel L. Watkins
//
// Copyright (C) 2015 Valpineware
// This file is licensed under the MIT License.
//==================================================================================================================|

#include <QtQuick/QQuickItem>
#include <QtQml>

#include <Parser/Parser.h>
#include <Graph/Graph.h>
#include <Mocker/Mocker.h>
#include <Compiler/Compiler.h>

#include "Application.h"

void Application::init()
{
	setSource(QUrl("qrc:///Main.qml"));
	setWidth(480);
	setHeight(240);

	//connect to compile button
	{
		QObject::connect(rootObject()->findChild<QObject*>("button_compile"), SIGNAL(clicked()),
						 this, SLOT(onButtonCompileClicked()));
		
		mTextField = rootObject()->findChild<QObject*>("textField_filepath");
	}
}


void Application::onButtonCompileClicked()
{
	using namespace vc;

	parser::Parser sourceParser;
	graph::Graph sourceGraph = sourceParser.parseFile("./Main.val");

	QString filepath = mTextField->property("text").toString();

	mocker::Mocker mocker;
	mocker.mock(sourceGraph);

	compiler::Compiler compiler;
	compiler.compile(mocker.outputFilepath());
}


void Application::keyPressEvent(QKeyEvent *ev)
{
	switch (ev->key())
	{
		case Qt::Key_Escape:
		{
			close();
			break;
		}
	}
}