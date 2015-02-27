//==================================================================================================================|
// Created 2015.02.08 by John Koehn
//
// Copyright (C) 2015 Valpineware
// This file is licensed under the MIT License.
//==================================================================================================================|

#include "Function.h"
#include "Utility.h"

namespace vc {	namespace mocker
{
	Function::Function(FileData &data)
	{
		const graph::Function *function = data.functions->dequeue();
		buildDeclartion(*function, data);

		DeclarationBlock::buildBlock(function->block(), data);
	}

	void Function::buildDeclartion(const graph::Function &function, FileData &data)
	{
		//build opening experssion
		QString declartion = Utility::createTabs(data.scope);
		declartion = function.returnType().fullType() + " " + function.id() + "(";

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
		data.body->append(declartion);
		
		if (function.id() != "main")
		{
			data.forwardDecs->append(declartion + ";");
		}
	}


}}