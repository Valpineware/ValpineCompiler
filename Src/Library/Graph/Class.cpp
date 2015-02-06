//==================================================================================================================|
// Created 2015.02.05 by Daniel L. Watkins
//
// Copyright (C) 2015 Valpineware
// This file is licensed under the MIT License.
//==================================================================================================================|

#include "Class.h"

namespace vc { namespace graph
{
	Class* Class::createFromVerbatimSignature(const QString &signature)
	{
		QStringList list = signature.split(QRegExp("\\s"));
		if (list.count() != 2)
			return nullptr;

		QStringListIterator iter(list);

		if (iter.next() != "class")
			return nullptr;

		const QString &cmp = iter.next();

		if (gRegExp_identifier.exactMatch(cmp))
		{
			Class *newClass = new Class(signature);
			newClass->mId = cmp;
			return newClass;
		}

		return nullptr;
	}
}}