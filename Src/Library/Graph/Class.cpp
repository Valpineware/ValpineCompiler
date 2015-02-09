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
		//can this possibly be a class declaration?
		{
			int colonCount = signature.count(":");
			int openCount = signature.count("<");
			int closedCount = signature.count(">");

			if (colonCount > 1 || openCount > 1 || closedCount != openCount)
				return nullptr;
		}

		QString filtered = signature;
		Utility::breakUpOperators(filtered, QStringList() << ":" << "<" << ">");
		QStringList list;
		Utility::breakUpByWhitespace(filtered, list);

		if (list.count() < 2)
			return nullptr;


		

		QStringListIterator iter(list);

		if (iter.next() != "class")
			return nullptr;

		
		Class *newClass = nullptr;

		//get the class id
		{
			const QString &cmp = iter.next();
			if (gRegExp_identifier.exactMatch(cmp))
			{
				newClass = new Class(signature);
				newClass->mId = cmp;
			}
		}

		//if there is a colon next, then look for super classes
		if (iter.hasNext())
		{
			if (iter.next() == ":")
			{
				AccessIdPair currentSuper;

				while (iter.hasNext())
				{
					const QString &cmp = iter.next();

					if (cmp == "<")
					{
						break;
					}
					if (cmp == "public")
					{
						currentSuper.accessType = AccessType::Public;
					}
					else if (Utility::couldBeIdentifier(cmp))
					{
						currentSuper.id = cmp;
						newClass->mSuperClasses.append(currentSuper);
					}
				}

				if (!iter.hasNext())
					return newClass;
			}
			else
				return nullptr;
		}
		else
			return newClass;

		return nullptr;
	}
}}