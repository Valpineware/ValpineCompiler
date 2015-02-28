//==================================================================================================================|
// Created 2015.02.28 by Daniel L. Watkins
//
// Copyright (C) 2015 Valpineware
// This file is licensed under the MIT License.
//==================================================================================================================|

#include "ParseScript.h"

namespace ext
{
	bool ParseScript::parse(const QString &filepath)
	{
		mGraph = Graph();
		QFile file(filepath);

		if (!file.open(QIODevice::ReadOnly))
			return false;

		QTextStream textStream(&file);
		int lineNumber = 0;
		while (!textStream.atEnd())
		{
			parseLine(textStream.readLine(), lineNumber++);
		}

		return true;
	}


	bool ParseScript::parseLine(const QString &line, int lineNumber)
	{
		//each leading tab increases the level
		int indentation = 0;
		int lastLeadingTab = 0;
		for (int i=0; i<line.count(); i++)
		{
			if (line[i] == "\t")
				indentation++;
			else
			{
				lastLeadingTab = i;
				break;
			}
		}

		//figure out the keyword
		int space = line.indexOf(QRegExp("[\t ]"), lastLeadingTab+1);
		if (space == -1)
		{
			qDebug() << "ParseScript: Error parsing line " << lineNumber;
			return false;
		}

		QStringRef keyword = line.midRef(lastLeadingTab, space-lastLeadingTab);

		//everything else is the verbatim string
		QStringRef verbatim = line.rightRef(line.count()-space-1);

		applyStatement(indentation, keyword, verbatim);

		return true;
	}


	void ParseScript::applyStatement(int indentation, const QStringRef &keyword, const QStringRef &verbatim)
	{
		qDebug() << indentation << " " << keyword << " " << verbatim;
	}
};