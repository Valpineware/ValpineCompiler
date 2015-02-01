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
		QString returnType = "(void|int|bool|float|double)";
		QString id = "\\w+";

		QString argStart = "\\(";
		QString argEnd = "\\)\\s*";

		QRegExp exp("\\s*"+returnType+"\\s+"+id+"\\s*"+argStart+"\\s*"+argEnd);

		return exp.exactMatch(testStr);
	}
}}