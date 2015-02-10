//==================================================================================================================|
// Created 2015.01.29 by Daniel L. Watkins
//
// Copyright (C) 2015 Valpineware
// This file is licensed under the MIT License.
//==================================================================================================================|

#include "Function.h"
#include "Utility.h"

namespace vc { namespace graph
{
	bool couldThisPossiblyBeAFunction(const QString &signature)
	{
		//there should be exactly one ( and one )
		if (signature.count("(") != 1 || signature.count(")") != 1)
			return false;

		if (signature.contains(";"))
			return false;

		return true;
	}


	graph::Function* parseType(QStringListIterator &i, graph::Function *function)
	{
		TypeExpression te;
		if (!Utility::parseTypeExpression(i,te))
			return nullptr;

		function->setReturnType(te);

		//	c) Identifier
		if (i.hasNext())
		{
			const QString &cmp = i.next();

			if (gRegExp_identifier.exactMatch(cmp))
				function->setId(cmp);
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
			graph::Parameter prm;
			QString typeBuffer;
			bool foundBaseType = false;
			bool foundEndTag = false;

			//are we at a comma?
			if (i.hasNext() && QRegExp("\\s*,\\s*").exactMatch(i.next()))
				continue;
			else
				i.previous();


			//get the return type
			while (i.hasNext())
			{
				const QString &cmp = i.next();

				if (cmp.contains(")"))
				{
					foundEndTag = true;
					break;
				}
				else if (gRegExp_typeMod.exactMatch(cmp))
				{
					typeBuffer.append(" "+cmp);
				}
				else if (!foundBaseType && gRegExp_typeId.exactMatch(cmp))
				{
					foundBaseType = true;
					typeBuffer.append(" "+cmp);
				}
				else if (typeBuffer.isEmpty())
					return nullptr;								//Error: No valid return type
				else
				{
					i.previous();
					break;
				}
			}

			prm.type = graph::TypeExpression(typeBuffer);

			//get the argument name
			if (i.hasNext())
			{
				const QString &cmp = i.next();

				if (gRegExp_identifier.exactMatch(cmp))
				{
					prm.id = cmp;
				}
				else
					return nullptr;								//Error: invalid identifier
			}
			else if (!foundEndTag)
				return nullptr;									//Error: nothing following return type


			//default value?
			if (i.hasNext())
			{
				const QString &cmp = i.next();
				
				if (QRegExp("\\s*=\\s*").exactMatch(cmp))
				{
					if (i.hasNext())
					{
						prm.defaultValue = i.next();
					}
				}
				else
				{
					i.previous();
				}

				function->addParameter(prm);
			}
		}

		return function;
	}


	Function* Function::createFromVerbatimSignature(const QString &signature)
	{
		if (!couldThisPossiblyBeAFunction(signature))
			return nullptr;

		
		QString filtered = signature;
		Utility::breakUpOperators(filtered, QStringList() << "(" << ")" << "," << "=" << "*" << "&");

		QStringList list;
		Utility::breakUpByWhitespace(filtered, list);
		QStringListIterator i(list);

		graph::Function *function = new graph::Function(signature);

		//Return type
		if (! parseType(i, function))
			return nullptr;

		//is it time for arguments yet?
		if (i.hasNext())
		{
			if (!i.next().contains("("))
				return nullptr;
		}

		//Parameters
		if (!parseParameters(i, function))
			return nullptr;

		return function;
	}
}}