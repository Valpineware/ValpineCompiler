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
	Utility::ReservedIds Utility::mReservedIds = Utility::buildReservedIds();

	Utility::ReservedIds Utility::buildReservedIds()
	{
		ReservedIds rid;

		rid.general << "asm" << "decltype" << "delete" << "explicit" << "false" << "final" << "inline" << "new" << "override" << "nullptr" << "sizeof" << "static_assert" << "template" << "this" << "true" << "typeid" << "typename" << "using";
		rid.general << "const" << "mutable" << "static" << "virtual" << "volatile";
		
		rid.types << "auto" << "bool" << "char" << "float" << "int" << "long" << "short" << "signed" << "unsigned" << "void";
		rid.control << "break" << "case" << "catch" << "continue" << "default" << "do" << "else"  << "elseif" << "for" << "goto" << "if" << "return" << "switch" << "throw" << "try" << "while";
		rid.typeDeclarators << "class" << "enum" << "namespace" << "struct" << "typedef" << "union";
		rid.access << "friend" << "operator" << "private" << "protected" << "public";
		rid.casting << "const_cast" << "dynamic_cast" << "reinterpret_cast" << "static_cast";

		return rid;
	}


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

		while (i.hasNext())
		{
			const QString &cmp = i.next();

			if (gRegExp_typeMod.exactMatch(cmp))
				type.append(" "+cmp);
			else if (!foundBaseType && Utility::couldBeTypeIdentifier(cmp))
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


	bool Utility::couldBeIdentifier(const QString &what)
	{
		if (!gRegExp_identifier.exactMatch(what))
			return false;
		
		if (mReservedIds.anyContain(what))
			return false;

		return true;
	}


	bool Utility::couldBeTypeIdentifier(const QString &what)
	{
		if (!gRegExp_identifier.exactMatch(what))
			return false;

		if (!mReservedIds.types.contains(what)  &&  mReservedIds.anyContain(what))
			return false;

		return true;
	}


	bool Utility::couldBeNumericConstant(const QString &what)
	{
		return gRegExp_numericConstant.exactMatch(what);
	}


	void Utility::breakUpOperators(QString &what, const QStringList &operators)
	{
		for (const QString &op : operators)
			what.replace(op, " "+op+" ");
	}


	Class::AccessType Utility::accessTypeForString(const QString what)
	{
		if (QRegExp("\\s*public\\s*:?\\s*").exactMatch(what))
			return Class::Public;
		else if (QRegExp("\\s*protected\\s*:?\\s*").exactMatch(what))
			return Class::Protected;
		else if (QRegExp("\\s*private\\s*:?\\s*").exactMatch(what))
			return Class::Private;

		return Class::None;
	}
}}