//==================================================================================================================|
// Created 2015.02.08 by John Koehn
//
// Copyright (C) 2015 Valpineware
// This file is licensed under the MIT License.
//==================================================================================================================|

#include "Function.h"

namespace vc {	namespace mocker
{
	void Function::buildDeclartion(graph::Function &function)
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




}}