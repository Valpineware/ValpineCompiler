//==================================================================================================================|
// Created 2015.02.19 by John Koehn
//
// Copyright (C) 2015 Valpineware
// This file is licensed under the MIT License.
//==================================================================================================================|

#include "ControlStructure.h"
#include "Function.h"
#include "DecelerationBlock.h"
#include "Utility.h"

namespace vc { namespace mocker
{
	//TODO ADD DEPTH LEVEL FOR INTERNAL TABBING
	ControlStructure::ControlStructure(graph::ControlStructure &controlStructure, Data &data)
	{
		buildStatement(controlStructure, data);
		DecelerationBlock::buildBlock(controlStructure.block(), data);
	}


	void ControlStructure::buildStatement(graph::ControlStructure &controlStructure, Data &data)
	{
		QString statement = Utility::createTabs(data.scope);
		statement += controlStructure.name() + "(" + controlStructure.expression() + ")";
		data.body->append(statement);
	}
}}