//==================================================================================================================|
// Created 2015.01.31 by Daniel L. Watkins
//
// Copyright (C) 2015 Valpineware
// This file is licensed under the MIT License.
//==================================================================================================================|

#include "Recognizer.h"

namespace vc { namespace parser
{
	const QRegExp gRegExp_identifier = QRegExp("([A-Za-z_]\\w*)");
	const QRegExp gRegExp_typeMod = QRegExp("(const|&|\\*|\\s)*");
	const QRegExp gRegExp_typeId = QRegExp("(const|&|\\*|\\s|([A-Za-z_]\\w*))*");


	bool couldThisPossiblyBeAFunction(const QString &signature)
	{
		//there should be exactly one ( and one ) TODO chop comments before this in the future
		if (!signature.contains("(") || !signature.contains(")"))	//TODO we should actually check the count here, because you can only have 1 of each
			return false;

		if (signature.contains(";"))
			return false;

		return true;
	}


	void preProcessFunctionSignature(QString &signature, QStringList &list)
	{
		signature.replace("(", " ( ");
		signature.replace(")", " ) ");
		signature.replace(",", " , ");
		signature.replace("=", " = ");

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


	graph::Function* parseType(QStringListIterator &i, graph::Function *function)
	{
		//TODO use the new QRegularExpression class instead
		QString returnType;
		bool foundBaseType = false;
			
		while (i.hasNext())
		{
			const QString &cmp = i.next();

			if (gRegExp_typeMod.exactMatch(cmp))
				returnType.append(" "+cmp);
			else if (!foundBaseType && gRegExp_typeId.exactMatch(cmp))
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

			if (gRegExp_identifier.exactMatch(cmp))
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
			graph::Parameter prm;
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
					prm.type.append(" "+cmp);
				else if (!foundBaseType && gRegExp_typeId.exactMatch(cmp))
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


	graph::Function* Recognizer::parseFunctionSignature(const QString &signature)
	{
		if (!couldThisPossiblyBeAFunction(signature))
			return nullptr;

		graph::Function *function = new graph::Function(signature);
		QString filtered = signature;
		QStringList list;
		preProcessFunctionSignature(filtered, list);
		QStringListIterator i(list);

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

		return function;
	}
}}