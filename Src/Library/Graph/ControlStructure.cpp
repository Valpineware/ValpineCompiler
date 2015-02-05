//==================================================================================================================|
// Created 2015.02.02 by Daniel L. Watkins
//
// Copyright (C) 2015 Valpineware
// This file is licensed under the MIT License.
//==================================================================================================================|

#include "ControlStructure.h"

namespace vc { namespace graph
{
	struct Type
	{
		//blank indicates no keyword associated and should not be parsed
		QString startKeyword = "";
		bool needsStartExp = false;
	};

	QList<Type> registeredNames()
	{
		QList<Type> list;

		#define A(start, need) {Type t; t.startKeyword = start; t.needsStartExp = need; list.append( t );}

		A("for", true)
		A("while", true)
		A("if", true)
		A("elseif", true)
		A("else", false)

		#undef A
		return list;
	} QList<Type> gRegisteredNames = registeredNames();


	QRegExp registeredNamesRegExp()
	{
		QString buffer;
		buffer.reserve(gRegisteredNames.count() * 4);

		for (Type t : gRegisteredNames)
		{
			buffer.append(t.startKeyword + "|");
		}

		if (buffer.at(buffer.count()-1) == "|")
			buffer.chop(1);

		return QRegExp(buffer);
	} QRegExp gRegisteredNamesRegExp = registeredNamesRegExp();


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
		QStringList list;
		QString filtered = signature;
		preProcessControlStructureSignature(filtered, list);
		QStringListIterator i(list);

		ControlStructure *cs = new ControlStructure(signature);

		//get the name
		if (i.hasNext())
		{
			const QString &cmp = i.next();

			if (gRegisteredNamesRegExp.exactMatch(cmp))
				cs->setName(cmp);
			else
				return nullptr;
		}
		else
			return nullptr;

		//what registered type of control structure is this?
		Type type;
		for (Type &t : gRegisteredNames)
		{
			if (t.startKeyword == cs->name())
			{
				type = t;
				break;
			}
		}

		if (!type.needsStartExp)
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