//==================================================================================================================|
// Created 2015.01.29 by Daniel L. Watkins
//
// Copyright (C) 2015 Valpineware
// This file is licensed under the MIT License.
//==================================================================================================================|

#include "Application.h"

void Application::init()
{
	setSource(QUrl("qrc:///Main.qml"));
	setWidth(800);
	setHeight(600);
}