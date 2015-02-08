//==================================================================================================================|
// Created 2015.02.08 by Daniel L. Watkins
//
// Copyright (C) 2015 Valpineware
// This file is licensed under the MIT License.
//==================================================================================================================|

#include "Utility.h"
#include "TypeExpression.h"

namespace vc { namespace graph
{
	void Utility::breakUpByWhitespace(const QString &what, QStringList &list)
	{
		list = what.split(QRegExp("\\s"));

		//remove all remaining whitespace strings
		QMutableStringListIterator mi(list);
		while (mi.hasNext())
		{
			if (QRegExp("\\s*").exactMatch(mi.next()))
				mi.remove();
		}
	}


	bool Utility::parseTypeExpression(QStringListIterator &i, TypeExpression &typeExpression)
	{
		QString type;
		bool foundBaseType = false;

		//TODO the following loop is redundant. It's used in Function, ControlStructure, and here
		while (i.hasNext())
		{
			const QString &cmp = i.next();

			if (gRegExp_typeMod.exactMatch(cmp))
				type.append(" "+cmp);
			else if (!foundBaseType && gRegExp_typeId.exactMatch(cmp))
			{
				foundBaseType = true;
				type.append(" "+cmp);
			}
			else if (type.isEmpty())
				return false;								//Error: No valid return type
			else
			{
				i.previous();
				typeExpression = TypeExpression(type);
				return true;
			}
		}

		return false;
	}
}}