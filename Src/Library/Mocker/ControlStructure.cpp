//==================================================================================================================|
// Created 2015.02.19 by John Koehn
//
// Copyright (C) 2015 Valpineware
// This file is licensed under the MIT License.
//==================================================================================================================|

#include "ControlStructure.h"
#include "Function.h"
#include "DeclarationBlock.h"
#include "Utility.h"

namespace vc { namespace mocker
{
	ControlStructure::ControlStructure(graph::ControlStructure &controlStructure, MockerData &data, QQueue<const graph::Function*> &functions)
	{
		buildStatement(controlStructure, data, functions);
		DeclarationBlock::buildBlock(controlStructure.block(), data, functions);
	}


	void ControlStructure::buildStatement(graph::ControlStructure &controlStructure, MockerData &data, QQueue<const graph::Function*> &functions)
	{
		QString statement = Utility::createTabs(data.scope);
		statement += controlStructure.name();

		if (controlStructure.name() != "else")
		{
			statement += "(" + controlStructure.expression() + ")";
		}
		data.body.append(statement);
	}
}}