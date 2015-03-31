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
	void Variable::createVar(MockerData &data, graph::Variable &var)
	{
		data.body.append(Utility::createTabs(data.scope) + createVarInternal(var));
	}

	void Variable::createVarClass(MockerData &data, graph::Variable &var, QString &classID, const ScopeState state)
	{
		QString cppVar = Utility::createTabs(data.header.getScopeLevel()) + createVarInternal(var);
		data.header.addClassMember(classID, cppVar, state);
	}

	QString Variable::createVarInternal(graph::Variable &var)
	{
		QString cppVar = var.typeExpression().fullType() + " " + var.id();

		if (var.initExpression() != "")
		{
			cppVar += " = " + var.initExpression();
		}

		cppVar += ";";

		return cppVar;
	}
}}