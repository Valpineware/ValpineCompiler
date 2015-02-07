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

using namespace vc;

void Application::init()
{
	setSource(QUrl("qrc:///Main.qml"));
	setWidth(480);
	setHeight(240);

	//connect to compile button
	{
		QObject::connect(rootObject()->findChild<QObject*>("button_compile"), SIGNAL(clicked()),
						 this, SLOT(onButtonCompileClicked()));
		
		mTextField_parseFilepath = rootObject()->findChild<QObject*>("textField_parseFilepath");
		mTextField_mockFilepath = rootObject()->findChild<QObject*>("textField_mockFilepath");
		mTextField_outputFilepath = rootObject()->findChild<QObject*>("textField_outputFilepath");
	}
}


void Application::onButtonCompileClicked()
{
	// 1. Parse from Valpine
	parser::Parser sourceParser;
	QString parseFilepath = mTextField_parseFilepath->property("text").toString();

	if (!sourceParser.parseFile(parseFilepath))
	{
		qDebug() << "Unable to parse " << parseFilepath;
		return;
	}
	
	// 2. Mock to C++
	mocker::Mocker mocker;
	QString mockFilepath = mTextField_mockFilepath->property("text").toString();
	if (!mocker.mock(sourceParser.graph(), mockFilepath))
		return;
	
	// 3. Compile to Executable
	compiler::Compiler compiler;
	compiler.compile(mockFilepath, mTextField_outputFilepath->property("text").toString());
}


void Application::keyPressEvent(QKeyEvent *ev)
{
	QQuickView::keyPressEvent(ev);

	switch (ev->key())
	{
		case Qt::Key_Escape:
		{
			close();
			break;
		}
	}
}