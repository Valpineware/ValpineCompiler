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
		void appendPreModifier(const QString &preModifier) { mPreModifiers.append(preModifier); }
		void appendPostModifier(const QString &postModifier) { mPostModifiers.append(postModifier); }
		void setBaseType(const QString &baseType) { mBaseType = baseType; }

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

	private:
		QVector<QString> mPreModifiers, mPostModifiers;
		QString mBaseType;
	};
}}

#endif
