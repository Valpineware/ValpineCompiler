//==================================================================================================================|
// Created 2015.02.20 by Daniel L. Watkins
//
// Copyright (C) 2015 Valpineware
// This file is licensed under the MIT License.
//==================================================================================================================|

#include "Expression.h"
#include "Utility.h"

namespace vc { namespace graph { namespace expression
{
	Expression::Expression(const QString &verbatim) :
		Component(verbatim)
	{
		QString filtered = verbatim;
		Utility::breakUpOperators(filtered);
		QStringList strList;
		Utility::breakUpByWhitespace(filtered, strList);

		QVector<QString> cmps = strList.toVector();
		
		for (int i=0; i<cmps.count(); i++)
		{
			const QString &str = cmps[i];
			
			if (str == "(")
			{
				int last = cmps.lastIndexOf(")");
				if (last == -1)
					continue;

				QString body = Utility::flatten(cmps.mid(i+1, last-i-1));

				bool couldBeArgumentList = false;
				if (!components().isEmpty())
					couldBeArgumentList = dynamic_cast<Id*>(components().last()) != nullptr;

				if (couldBeArgumentList)
				{
					if (auto prev = dynamic_cast<Id*>(components().last()))
						prev->setType(Id::Type::FunctionCall);

					components().append(new Arguments(body));
				}
				else
					components().append(new Expression(body));

				i = last;
			}
			else if (Utility::couldBeIdentifier(str) || Utility::couldBeNumericConstant(str))
				components().append(new Id(str));
			else
				components().append(new Operator(str));
		}
	}


	Arguments::Arguments(const QString &verbatim) :
		Component("")
	{
		if (!verbatim.isEmpty())
		{
			QVector<int> rootCommaPos(1, 0);
			int level = 0;

			//find the positions of root level commas
			for (int i=0; i<verbatim.count(); i++)
			{
				QChar c = verbatim[i];

				if (c == "," && level == 0)
				{
					//only add if there is anything after this comma
					if (verbatim.count() > i+1)
						rootCommaPos.append(i+1);
				}
				else if (c == "(")
					level++;
				else if (c == ")")
					level--;
			}

			QList<QStringRef> chunks;

			//split verbaitm on all the positions found
			for (int i=0; i<rootCommaPos.count(); i++)
			{
				int current = rootCommaPos[i];

				if (i+1 < rootCommaPos.count())
				{
					int next = rootCommaPos[i+1];
					chunks.append(verbatim.midRef(current, next-current-1));
				}
				else
				{
					chunks.append(verbatim.midRef(current));
				}
			}

			for (QStringRef &str : chunks)
				components().append(new Expression(str.toString()));
		}
	}
}}}