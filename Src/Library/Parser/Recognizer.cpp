//==================================================================================================================|
// Created 2015.01.31 by Daniel L. Watkins
//
// Copyright (C) 2015 Valpineware
// This file is licensed under the MIT License.
//==================================================================================================================|

#include "Recognizer.h"

namespace vc { namespace parser
{
	bool Recognizer::isFunctionHeader(const QString &testStr)
	{
		QString typeMod = "(const|&|\\*|\\s)*";
		QString identifier = "[A-Za-z_]\\w*";

		QString argStart = "\\(";
		QString argEnd = "\\)\\s*";

		QRegExp exp("\\s*" + typeMod + identifier + typeMod + "\\s+" + identifier + "\\s*" + argStart + "\\s*" + argEnd);

		return exp.exactMatch(testStr);
	}
}}