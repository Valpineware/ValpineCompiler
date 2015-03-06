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
	Utility::ReservedIds gReservedIds;

	STATIC_BLOCK_UNSAFE(BuildReservedIds,
		gReservedIds.general << "asm" << "decltype" << "delete" << "explicit" << "false" << "final" << "inline" << "new" << "override" << "nullptr" << "sizeof" << "static_assert" << "template" << "this" << "true" << "typeid" << "typename" << "using";
		gReservedIds.general << "const" << "mutable" << "static" << "virtual" << "volatile";
		
		gReservedIds.types << "auto" << "bool" << "char" << "float" << "int" << "long" << "short" << "signed" << "unsigned" << "void";
		gReservedIds.control << "break" << "case" << "catch" << "continue" << "default" << "defer" << "else"  << "elseif" << "for" << "goto" << "if" << "return" << "switch" << "throw" << "try" << "while";
		gReservedIds.typeDeclarators << "class" << "enum" << "namespace" << "struct" << "typedef" << "union";
		gReservedIds.access << "friend" << "operator" << "private" << "protected" << "public";
		gReservedIds.casting << "const_cast" << "dynamic_cast" << "reinterpret_cast" << "static_cast";
	);


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
	{	//TODO move into TypeExpression constructor
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
		
		if (gReservedIds.anyContain(what))
			return false;

		//are any of the character operators?
		for (int i=0; i<what.count(); i++)
		{
			if (gRegExp_operatorChar.exactMatch(what.at(i)))
				return false;
		}

		return true;
	}


	bool Utility::couldBeTypeIdentifier(const QString &what)
	{
		if (!gRegExp_identifier.exactMatch(what))
			return false;

		if (!gReservedIds.types.contains(what)  &&  gReservedIds.anyContain(what))
			return false;

		return true;
	}


	bool Utility::couldBeNumericConstant(const QString &what)
	{
		return gRegExp_numericConstant.exactMatch(what);
	}


	bool Utility::isReservedWord_control(const QString &what)
	{
		return gReservedIds.control.contains(what);
	}


	void Utility::breakUpOperators(QString &what)
	{
		static QVector<QStringList> tiers(3);

		STATIC_BLOCK_UNSAFE(Tiers,
			tiers[2] << "->*" << "<<=" << ">>=";
			tiers[1] << "++" << "--" << "->" << "<<" << ">>" << "::" << "<=" << ">=" << "!=" << "==" << "&&" << "||" << "+=" << "-=" << "/=" << "*=" << "%=" << "&=" << "^=" << "|=" << ".*";
			tiers[0] << "+" << "-" << "*" << "/" << "!" << "~" << "&" << "|" << "^" << "%" << "=" << "<" << ">" << "?" << ":" << "," << "(" << ")";
		);

		QStringList chunks;
		const int reach = tiers.count();
				
		for (int i=0; i<what.count(); i++)
		{
			//could this character even be part of an operator?
			if (gRegExp_operatorChar.exactMatch(what.at(i)))
			{
				bool matched = false;

				for (int reduction=0; reduction<reach && !matched; reduction++)
				{
					int actualReach = reach-reduction;
					QStringRef chunk = what.midRef(i, actualReach);

					for (const QString &str : tiers[chunk.count()-1])
					{
						if (chunk == str)
						{
							chunks.append(chunk.toString());
							matched = true;
							int delta = chunks.last().count()-1; //one less since the for loop will increment it anyways
							i += delta;
							chunks.append(""); //append blank so this operator is isolated
							break;
						}
					}
				}
			}
			else if (chunks.isEmpty())
			{
				chunks.append(what.at(i));
			}
			else
			{
				chunks.last().append(what.at(i));
			}
		}

		what = flatten(chunks, " ");
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