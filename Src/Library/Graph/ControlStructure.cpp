//==================================================================================================================|
// Created 2015.02.02 by Daniel L. Watkins
//
// Copyright (C) 2015 Valpineware
// This file is licensed under the MIT License.
//==================================================================================================================|

#include "ControlStructure.h"

namespace vc { namespace graph
{
	void preProcessControlStructureSignature(QString &signature, QStringList &list)
	{
		signature.replace("(", " ( ");
		signature.replace(")", " ) ");

		//3) Split into a list deliminated by " "
		list = signature.split(QRegExp("\\s"));

		//remove all remaining whitespace strings
		QMutableStringListIterator mi(list);
		while (mi.hasNext())
		{
			if (QRegExp("\\s*").exactMatch(mi.next()))
				mi.remove();
		}
	}


	ControlStructure* ControlStructure::createFromVerbatimSignature(const QString signature)
	{
		if ((signature.count("(") < 1 || signature.count(")") < 1))
			return nullptr;

		QStringList list;
		QString filtered = signature;
		preProcessControlStructureSignature(filtered, list);
		QStringListIterator i(list);

		ControlStructure *cs = new ControlStructure(signature);

		//get the name
		if (i.hasNext())
		{
			const QString &cmp = i.next();

			if (QRegExp("for|while|if|else if|else").exactMatch(cmp))
				cs->setName(cmp);
			else
				return nullptr;
		}
		else
			return nullptr;

		//this is sort of a hack, but what else should be done?
		if (cs->name() == "else")
			return cs;

		//there should be an opening parenthesis next and a closing one at the very end
		if (!i.hasNext() || i.next() != "(" || list.last() != ")")
			return nullptr;

		//now just copy everything between the two () and set that as the expression
		int openIndex = signature.indexOf("(")+1;
		int closeIndex = signature.lastIndexOf(")"); 
		cs->setExpression(signature.mid(openIndex, closeIndex-openIndex));

		return cs;
	}
}}