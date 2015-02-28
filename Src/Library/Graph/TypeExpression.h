//==================================================================================================================|
// Created 2015.02.01 by Daniel L. Watkins
//
// Copyright (C) 2015 Valpineware
// This file is licensed under the MIT License.
//==================================================================================================================|

#ifndef _vc_parser_TypeExpression_h
#define _vc_parser_TypeExpression_h

#include <Library.h>

namespace vc { namespace graph
{
	/**
	 * @brief Represents a type expression used in declarations, return types, parameters, etc.
	 *
	 * A type expression is the combination of a BaseType and various modifiers such as "const", "&", etc.
	 * There are 3 components to a TypeExpression: Pre modifiers, the BaseType, and post modifiers.
	 */
	class TypeExpression
	{
	public:
		TypeExpression()
		{
		}

		TypeExpression(const QString &verbatim)
		{
			QString filtered = verbatim;
			filtered.replace("*", " * ");
			filtered.replace("&", " & ");

			bool foundBaseType = false;
			QStringList list = filtered.split(QRegExp("\\s"));
			list.removeAll("");

			for (QString s : list)
			{
				if (QRegExp("const|\\*|&").exactMatch(s))
				{
					if (foundBaseType)
						mPostModifiers.append(s);
					else
						mPreModifiers.append(s);
				}
				else if (!foundBaseType)
				{
					mBaseType = s;
					foundBaseType = true;
				}
				else
				{
					qDebug() << "Unknown string component in type expression verbatim";
				}
			}
		}


		const QVector<QString>& preModifiers() const { return mPreModifiers; }
		const QVector<QString>& postModifiers() const { return mPostModifiers; }
		QString baseType() const { return mBaseType; }


		QString fullType() const
		{
			QString fullType;
			fullType.reserve((mPreModifiers.count()+mPostModifiers.count()+1) * 5);	//NOTE an arbitrary approximation

			for (QString s : mPreModifiers)
				fullType.append(s+" ");

			fullType.append(mBaseType+" ");

			for (QString s : mPostModifiers)
				fullType.append(s+" ");

			if (!fullType.isEmpty() && fullType.at(fullType.count()-1) == " ")
				fullType.chop(1);

			return fullType;
		}


		bool operator==(const TypeExpression &rhs) const
		{
			return mPreModifiers == rhs.mPreModifiers &&
					mPostModifiers == rhs.mPostModifiers &&
					mBaseType == rhs.mBaseType;
		}

	private:
		QVector<QString> mPreModifiers, mPostModifiers;
		QString mBaseType;
	};
}}

#endif
