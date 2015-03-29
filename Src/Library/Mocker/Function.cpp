//==================================================================================================================|
// Created 2015.02.08 by John Koehn
//
// Copyright (C) 2015 Valpineware
// This file is licensed under the MIT License.
//==================================================================================================================|

#include "Function.h"
#include "Utility.h"
#include "DeclarationBlock.h"

namespace vc {	namespace mocker
{
	Function::Function(MockerData &data, const graph::Function &function, const QString &classID, QQueue<const graph::Function*> &functions, const ScopeState state)
	{
		buildDeclartion(data, function, classID, state);

		DeclarationBlock::buildBlock(function.block(), data, functions);
	}

	void Function::buildDeclartion(MockerData &data, const graph::Function &function, const QString &classID, const ScopeState state)
	{
		//build opening experssion
		QString declartion = Utility::createTabs(data.scope);

		//check if we are building a method
		if (classID != "")
		{
			declartion += classID + "::";
		}

		declartion += function.returnType().fullType() + " " + function.id() + "(";

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
		data.body.append(declartion);
		
		if (function.id() != "main")
		{
			if (classID != "")
			{
				data.header.addClassMember(classID, declartion, state);
			}
			else
			{
				data.header.addFunctionDec(declartion + ";");
			}
		}
	}


}}