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
		mBody = &body;
		mForwardDecs = &forwardDecs;
		mFunction = &function;

		buildDeclartion();
		buildBody();
	}

	void Function::buildDeclartion()
	{
		//build opening experssion
		mDeclartion = mFunction->returnType().fullType() + " " + mFunction->id() + "(";

		//add in the parameters
		const QVector<graph::Parameter> &param = mFunction->parameters();
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
		mBody->append(mDeclartion);
		
		if (mFunction->id() != "main")
		{
			mForwardDecs->append(mDeclartion + ";");
		}
	}

	void Function::buildBody()
	{

		QListIterator<graph::Statement*> iter(mFunction->block().statements());

		mBody->append("{");

		while (iter.hasNext())
		{
			graph::Statement *statement = iter.next();

			if (graph::Function *function = dynamic_cast<graph::Function*>(statement))
			{
				//hey, we have a nested function, store the knowledge and move on
				mNestedFunctions.enqueue(function);
			}
			else if (graph::Variable *variable = dynamic_cast<graph::Variable*>(statement))
			{
				Variable::createVar(*mBody, *variable);
			}
			else
			{
				mBody->append("\t" + statement->verbatim());
			}
		}


		mBody->append("}");
	}



}}