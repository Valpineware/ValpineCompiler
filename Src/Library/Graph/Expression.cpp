//==================================================================================================================|
// Created 2015.02.20 by Daniel L. Watkins
//
// Copyright (C) 2015 Valpineware
// This file is licensed under the MIT License.
//==================================================================================================================|

#include "Expression.h"
#include "Utility.h"

namespace vc { namespace graph { namespace expr
{
	Expression* Expression::make(const QString &verbatim)
	{
		QString filtered = verbatim;
		Utility::breakUpOperators(filtered);
		QStringList strList;
		Utility::breakUpByWhitespace(filtered, strList);

		QVector<QString> cmps = strList.toVector();
		Expression *expression = new Expression;
		
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
				if (!expression->components().isEmpty())
					couldBeArgumentList = dynamic_cast<Id*>(expression->components().last()) != nullptr;

				if (couldBeArgumentList)
				{
					if (auto prev = dynamic_cast<Id*>(expression->components().last()))
						prev->setType(Id::Type::FunctionCall);

					expression->components().append(Arguments::make(body));
				}
				else
					expression->components().append(Expression::make(body));

				i = last;
			}
			else if (Utility::couldBeIdentifier(str) || Utility::couldBeNumericConstant(str))
				expression->components().append(Id::make(str));
			else
				expression->components().append(Operator::make(str));
		}

		return expression;
	}


	Operator* Operator::make(const QString &verbatim)
	{
		Operator *op = new Operator;
		op->setVerbatim(verbatim);

		return op;
	}


	Id* Id::make(const QString &verbatim)
	{
		Id *id = new Id;
		id->setVerbatim(verbatim);

		return id;
	}


	Arguments* Arguments::make(const QString &verbatim)
	{
		Arguments *arguments = new Arguments;

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
			{
				auto exp = Expression::make(str.toString());

				if (exp->components().count() > 1 || exp->components().isEmpty())
					arguments->components().append(exp);

				//we don't need an extra Expression just to wrap this single Component
				else
				{
					Component *stolen = exp->components().first();
					exp->components().clear();
					arguments->components().append(stolen);
					delete exp;
				}
			}
		}

		return arguments;
	}
}}}