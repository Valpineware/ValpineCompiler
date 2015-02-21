//==================================================================================================================|
// Created 2015.02.08 by John Koehn
//
// Copyright (C) 2015 Valpineware
// This file is licensed under the MIT License.
//==================================================================================================================|

#include "Function.h"
#include "DecelerationBlock.h"

namespace vc {	namespace mocker
{
	Function::Function(QVector<QString> &body, QVector<QString> &forwardDecs, const graph::Function &function, int scope)
	{
		buildDeclartion(function, forwardDecs, body);

		DecelerationBlock::buildBlock(function.block(), body, forwardDecs, mNestedFunctions, scope);
	}

	void Function::buildDeclartion(const graph::Function &function, QVector<QString> &forwardDecs, QVector<QString> &body)
	{
		//build opening experssion
		QString declartion = function.returnType().fullType() + " " + function.id() + "(";

		//add in the parameters
		const QVector<graph::Parameter> &param = function.parameters();
		for (int i = 0; i < param.size(); i++)
		{
			declartion += param[i].type.fullType() + " " + param[i].id;

			//check if default value is needed, if so, add it
			if (param[i].defaultValue != "")
			{
				declartion += "=" + param[i].defaultValue;
			}

			if ((i + 1) != param.size())
			{
				declartion += ", ";
			}
		}

		declartion += ")";
		body.append(declartion);
		
		if (function.id() != "main")
		{
			forwardDecs.append(declartion + ";");
		}
	}


}}