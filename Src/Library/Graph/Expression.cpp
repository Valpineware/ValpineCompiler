//==================================================================================================================|
// Created 2015.02.20 by Daniel L. Watkins
//
// Copyright (C) 2015 Valpineware
// This file is licensed under the MIT License.
//==================================================================================================================|

#include "Expression.h"
#include "Utility.h"


namespace vc { namespace graph
{
	Expression::Expression(const QString &verbatim) :
		Statement(verbatim),
		mRoot(verbatim)
	{
	}


	QString flatten(const QVector<QString> &list)
	{
		QString buffer;
		buffer.reserve(3 * list.count());

		for (const QString &str : list)
			buffer.append(str);

		return buffer;
	}
	

	Expression::Result::Result(const QString &verbatim) :
		Component(verbatim)
	{
		QString filtered = verbatim;
		Utility::breakUpOperators(filtered, QStringList() << "++" << "(" << ")" << "+");
		QStringList strList;
		Utility::breakUpByWhitespace(filtered, strList);

		QVector<QString> components = strList.toVector();
		
		for (int i=0; i<components.count(); i++)
		{
			const QString &str = components[i];
			
			if (str == "(")
			{
				int last = components.lastIndexOf(")");
				if (last == -1)
					continue;

				QString body = flatten(components.mid(i+1, last-i-1));

				bool couldBeArgumentList = false;
				if (!mComponents.isEmpty())
					couldBeArgumentList = dynamic_cast<Id*>(mComponents.last()) != nullptr;

				if (couldBeArgumentList)
					mComponents.append(new Arguments(body));
				else
					mComponents.append(new Result(body));

				i = last;
			}
			else if (Utility::couldBeIdentifier(str) || Utility::couldBeNumericConstant(str))
				mComponents.append(new Id(str));
			else if (str == "++")
				mComponents.append(new Operator(str));
		}
	}


	Expression::Result::~Result()
	{
		for (Component *cmp : mComponents)
		{
			if (cmp) delete cmp;
		}
	}


	Expression::Arguments::Arguments(const QString &verbatim) :
		Component(verbatim)
	{
		if (!verbatim.isEmpty())
			mList.append(new Result(verbatim));
	}
}}