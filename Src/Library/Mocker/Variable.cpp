//==================================================================================================================|
// Created 2015.02.10 by John Koehn
//
// Copyright (C) 2015 Valpineware
// This file is licensed under the MIT License.
//==================================================================================================================|

#include "Variable.h"

namespace vc { namespace mocker
{
	void Variable::createVar(QVector<QString> &body, graph::Variable &var)
	{
		QString cppVar = var.typeExpression().fullType() + " " + var.id();

		if (var.initExpression() != "")
		{
			cppVar += " = " + var.initExpression();
		}

		cppVar += ";";
		body.append(cppVar);
	}
}}