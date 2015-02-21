//==================================================================================================================|
// Created 2015.02.10 by John Koehn
//
// Copyright (C) 2015 Valpineware
// This file is licensed under the MIT License.
//==================================================================================================================|

#include "Variable.h"
#include "Utility.h"

namespace vc { namespace mocker
{
	void Variable::createVar(QVector<QString> &body, graph::Variable &var, int scope)
	{
		QString cppVar = Utility::createTabs(scope);
		cppVar += var.typeExpression().fullType() + " " + var.id();

		if (var.initExpression() != "")
		{
			cppVar += " = " + var.initExpression();
		}

		cppVar += ";";
		body.append(cppVar);
	}
}}