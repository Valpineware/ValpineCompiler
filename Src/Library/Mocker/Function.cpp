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
	void Function::buildDeclartion(QVector<QString> &body, graph::Function &function)
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
	}

	//TODO, body.append(MDeclartion) MOVE OUT OF FUNCTION
	void Function::buildBody(QVector<QString> &body, graph::Block &block)
	{
		body.append(mDeclartion);
		QListIterator<graph::Statement*> iter(block.statements());

		body.append("{");

		while (iter.hasNext())
		{
			graph::Statement *statement = iter.next();

			if (graph::Function *function = dynamic_cast<graph::Function*>(statement))
			{
				//createFunction(*function);
				//buildBlock(function->block());
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