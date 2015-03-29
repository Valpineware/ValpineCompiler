//==================================================================================================================|
// Created 2015.02.20 by John Koehn
//
// Copyright (C) 2015 Valpineware
// This file is licensed under the MIT License.
//==================================================================================================================|

#include "Utility.h"
#include "Variable.h"
#include "ControlStructure.h"
#include "Function.h"

namespace vc { namespace mocker
{
	QString Utility::createTabs(int scopeLevel)
	{
		QString line;
		for (int i = 0; i < scopeLevel; i++)
		{
			line += "\t";
		}

		return line;
	}

	void Utility::vectorToStream(QTextStream &outStream, QVector<QString> &vecData)
	{
		for (QString line : vecData)
		{
			outStream << line << "\n";
		}
	}
}}