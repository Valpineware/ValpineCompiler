//==================================================================================================================|
// Created 2015.02.02 by Daniel L. Watkins
//
// Copyright (C) 2015 Valpineware
// This file is licensed under the MIT License.
//==================================================================================================================|

#include "ControlStructure.h"
#include "Utility.h"

namespace vc { namespace graph
{
	struct Type
	{
		QVector<QString> startKeywords;
		bool needsExpression = false;
	};


	QList<Type> gRegisteredTypes;

	#define A(start, need) {Type t; t.startKeywords << start; t.needsExpression = need; gRegisteredTypes.append( t );}
	STATIC_BLOCK_UNSAFE(RegisteredNames,
		A("for", true)
		A("while", true)
		A("defer" << "while", true)
		A("if", true)
		A("else" << "if", true)
		A("else", false)
	);
	#undef A


	ControlStructure* ControlStructure::make(const QString signature)
	{
		QStringList list;
		QString filtered = signature;
		Utility::breakUpOperators(filtered);
		Utility::breakUpByWhitespace(filtered, list);

		QStringListIterator i(list);
		ControlStructure *cs = new ControlStructure(signature);

		//read in the control keywords
		while (i.hasNext())
		{
			const QString &cmp = i.next();

			if (Utility::isReservedWord_control(cmp))
				cs->mKeywords.append(cmp);
			else if (cmp == "(")
			{
				i.previous();
				break;
			}
			else
				return nullptr;
		}

		const Type *type = nullptr;

		//match this up with a type
		for (const Type &t : gRegisteredTypes)
		{
			if (t.startKeywords == cs->mKeywords)
			{
				type = &t;
				break;
			}
		}

		if (type == nullptr)
			return nullptr;

		if (!type->needsExpression)
		{
			if (!i.hasNext())
				return cs;
			else
				return nullptr;
		}

		//there should be an opening parenthesis next and a closing one at the very end
		if (!i.hasNext() || i.next() != "(" || list.last() != ")")
			return nullptr;

		//now just copy everything between the two () and set that as the expression
		int openIndex = signature.indexOf("(")+1;
		int closeIndex = signature.lastIndexOf(")"); 
		cs->setExpression(signature.mid(openIndex, closeIndex-openIndex));

		return cs;
	}


	QString ControlStructure::name() const
	{
		return Utility::flatten(mKeywords, " ");
	}
}}