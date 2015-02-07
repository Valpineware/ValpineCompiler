//==================================================================================================================|
// Created 2015.02.06 by Daniel L. Watkins
//
// Copyright (C) 2015 Valpineware
// This file is licensed under the MIT License.
//==================================================================================================================|

#include "Variable.h"

namespace vc { namespace graph
{
	Variable* Variable::createFromVerbatimSignature(const QString signature)
	{
		QString filtered = signature;
		filtered.replace(";", "");
		filtered.replace("=", " = ");

		QStringList list = filtered.split(QRegExp("\\s"));

		//TODO this is duplicated in Function.cpp preProcessFunctionSignature
		QMutableStringListIterator mi(list);
		while (mi.hasNext())
		{
			if (QRegExp("\\s*").exactMatch(mi.next()))
				mi.remove();
		}

		if (list.count() < 2)
			return nullptr;

		QStringListIterator i(list);
		Variable *variable = new Variable(signature);
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
					return nullptr;								//Error: No valid return type
				else
				{
					i.previous();
					variable->setTypeExpression(graph::TypeExpression(type));
					break;
				}
			}
		}

		//identifier
		if (i.hasNext())
		{
			const QString &cmp = i.next();

			if (gRegExp_identifier.exactMatch(cmp))
				variable->setId(cmp);
		}
		else
			return nullptr;


		//optional initialization
		if (i.hasNext())
		{
			if (i.next() != "=" || !i.hasNext())
				return nullptr;

			//everything after the first "=" should be shoved into the init expression
			int index = signature.indexOf("=");
			variable->setInitExpression(signature.mid(index+1, signature.count()-index).remove(";").trimmed());
		}

		return variable;
	}
}}