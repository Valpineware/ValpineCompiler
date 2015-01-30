//==================================================================================================================|
// Created 2015.01.29 by Daniel L. Watkins
//
// Copyright (C) 2015 Valpineware
// This file is licensed under the MIT License.
//==================================================================================================================|

#include "Statement.h"

namespace vc { namespace graph
{
	bool isWhiteSpace(const QChar &c)
	{
		return c == " " || c == "\t" || c == "\n";
	}


	void Statement::removeLeadingTrailingWhiteSpace(QString &line)
	{
		//TODO naive approach here. Instead, mark how far in you can chop off in one go

		//remove leading white space
		while (!line.isEmpty() && isWhiteSpace(line[0]))
			line = line.right(line.count()-1);

		//remove trailing while space
		while (!line.isEmpty() && isWhiteSpace(line[line.count()-1]))
			line = line.left(line.count()-1);
	}
}}