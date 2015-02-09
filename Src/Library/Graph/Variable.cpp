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
		filtered.replace("*", " * ");
		filtered.replace("&", " & ");	//TODO this is redundantly performed in many other locations

		QStringList list;
		Utility::breakUpByWhitespace(filtered, list);

		if (list.count() < 2)
			return nullptr;

		QStringListIterator i(list);
		Variable *variable = new Variable(signature);

		TypeExpression te;
		if (!Utility::parseTypeExpression(i,te))
			return nullptr;

		variable->setTypeExpression(te);

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