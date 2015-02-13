//==================================================================================================================|
// Created 2015.02.08 by John Koehn
//
// Copyright (C) 2015 Valpineware
// This file is licensed under the MIT License.
//==================================================================================================================|

#include "Function.h"
#include "Variable.h"

namespace vc {	namespace mocker
{
	Function::Function(QVector<QString> &body, QVector<QString> &forwardDecs, graph::Function &function)
	{
		buildDeclartion(body, forwardDecs, function);
		buildBody(body, function);
	}

	void Function::buildDeclartion(QVector<QString> &body, QVector<QString> &forwardDecs, graph::Function &function)
	{
		//build opening experssion
		mDeclartion = function.returnType().fullType() + " " + function.id() + "(";

		//add in the parameters
		const QVector<graph::Parameter> &param = function.parameters();
		for (int i = 0; i < param.size(); i++)
		{
			mDeclartion += param[i].type.fullType() + " " + param[i].id;

			//check if default value is needed, if so, add it
			if (param[i].defaultValue != "")
			{
				mDeclartion += "=" + param[i].defaultValue;
			}

			if ((i + 1) != param.size())
			{
				mDeclartion += ", ";
			}
		}

		mDeclartion += ")";
		body.append(mDeclartion);
		
		if (function.id() != "main")
		{
			forwardDecs.append(mDeclartion + ";");
		}
	}

	void Function::buildBody(QVector<QString> &body, graph::Function &function)
	{

		QListIterator<graph::Statement*> iter(function.block().statements());

		body.append("{");

		while (iter.hasNext())
		{
			graph::Statement *statement = iter.next();

			if (graph::Function *function = dynamic_cast<graph::Function*>(statement))
			{
				//hey, we have a nested function, store the knowledge and move on
				mNestedFunctions.append(*function);
			}
			else if (graph::Variable *variable = dynamic_cast<graph::Variable*>(statement))
			{
				Variable::createVar(body, *variable);
			}
			else
			{
				body.append(statement->verbatim());
			}
		}


		body.append("}");
	}



}}