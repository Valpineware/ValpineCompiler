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
	ControlStructure::ControlStructure(graph::ControlStructure &controlStructure, FunctionData &data)
	{
		buildStatement(controlStructure, data);
		DeclarationBlock::buildBlock(controlStructure.block(), data);
	}


	void ControlStructure::buildStatement(graph::ControlStructure &controlStructure, FunctionData &data)
	{
		QString statement = Utility::createTabs(data.scope);
		statement += controlStructure.name();

		if (controlStructure.name() != "else")
		{
			statement += "(" + controlStructure.expression() + ")";
		}
		data.body->append(statement);
	}
}}