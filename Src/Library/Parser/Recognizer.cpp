//==================================================================================================================|
// Created 2015.01.31 by Daniel L. Watkins
//
// Copyright (C) 2015 Valpineware
// This file is licensed under the MIT License.
//==================================================================================================================|

#include "Recognizer.h"

namespace vc { namespace parser
{
	graph::Function* parseType(QStringListIterator &i, graph::Function *function)
	{
		//TODO use the new QRegularExpression class instead
		QRegExp typeMod("(const|&|\\*|\\s)*");
		QRegExp typeId("(const|&|\\*|\\s|([A-Za-z_]\\w*))*");
		QString returnType;
		bool foundBaseType = false;
			
		while (i.hasNext())
		{
			const QString &cmp = i.next();

			if (typeMod.exactMatch(cmp))
				returnType.append(" "+cmp);
			else if (!foundBaseType && typeId.exactMatch(cmp))
			{
				foundBaseType = true;
				returnType.append(" "+cmp);
			}
			else if (returnType.isEmpty())
				return nullptr;								//Error: No valid return type
			else
			{
				i.previous();
				function->setReturnType(returnType);
				break;
			}
		}			

		//	c) Identifier
		if (i.hasNext())
		{
			const QString &cmp = i.next();

			if (QRegExp("([A-Za-z_]\\w*)").exactMatch(cmp))
			{
				function->setId(cmp);
			}
			else
				return nullptr;								//Error: invalid identifier
		}
		else
			return nullptr;									//Error: nothing following return type

		return function;
	}



	graph::Function* parseParameters(QStringListIterator &i, graph::Function *function)
	{
		while (i.hasNext())
		{
			QRegExp typeMod("(const|&|\\*|\\s)*");
			QRegExp typeId("(const|&|\\*|\\s|([A-Za-z_]\\w*))*");
			graph::Parameter prm;
			bool foundBaseType = false;
			bool foundEndTag = false;

			//get the return type
			while (i.hasNext())
			{
				const QString &cmp = i.next();

				if (cmp.contains(")"))
				{
					foundEndTag = true;
					break;
				}
				else if (typeMod.exactMatch(cmp))
					prm.type.append(" "+cmp);
				else if (!foundBaseType && typeId.exactMatch(cmp))
				{
					foundBaseType = true;
					prm.type.append(" "+cmp);
				}
				else if (prm.type.isEmpty())
					return nullptr;								//Error: No valid return type
				else
				{
					i.previous();
					break;
				}
			}

			//get the argument name
			if (i.hasNext())
			{
				const QString &cmp = i.next();

				if (QRegExp("([A-Za-z_]\\w*)").exactMatch(cmp))
				{
					prm.id = cmp;
					function->addParameter(prm);
				}
				else
					return nullptr;								//Error: invalid identifier
			}
			else if (!foundEndTag)
				return nullptr;									//Error: nothing following return type
		}

		return function;
	}



	graph::Function* Recognizer::parseFunctionSignature(const QString &signature)
	{
		//early exit tests
		{
			//there should be exactly one ( and one ) TODO chop comments before this in the future
			if (!signature.contains("(") || !signature.contains(")"))	//TODO we should actually check the count here, because you can only have 1 of each
				return nullptr;

			if (signature.contains(";"))
				return nullptr;
		}

		graph::Function *function = new graph::Function(signature);
		QString filtered = signature;

		filtered.replace("(", " ( ");
		filtered.replace(")", " ) ");

		//3) Split into a list deliminated by " "
		QStringList list = filtered.split(QRegExp("\\s"));

		//remove all remaining whitespace strings
		QMutableStringListIterator mi(list);
		while (mi.hasNext())
		{
			if (QRegExp("\\s*").exactMatch(mi.next()))
				mi.remove();
		}

		QStringListIterator i(list);

		//4) Iterate through the list. Build the Function instance from here. If an error is detected, null the function instance and return
		//	a) Pre-Modifiers TODO

		//Return type
		if (! (function = parseType(i, function)))
			return nullptr;

		//is it time for arguments yet?
		if (i.hasNext())
		{
			if (!i.next().contains("("))
				return nullptr;
		}

		//Parameters
		if (! (function = parseParameters(i, function)))
			return nullptr;

		//	e) Post-Modifiers

		return function;
	}
}}