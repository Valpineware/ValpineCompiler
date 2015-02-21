//==================================================================================================================|
// Created 2015.02.20 by John Koehn
//
// Copyright (C) 2015 Valpineware
// This file is licensed under the MIT License.
//==================================================================================================================|

#include "Utility.h"
#include "Variable.h"
#include "ControlStructure.h"
#include "Function.h"

namespace vc { namespace mocker
{
	void Utility::buildBlock(const graph::Block &block, QVector<QString> &body)
	{
		QListIterator<graph::Statement*> iter(block.statements());

		body.append("{");

		while (iter.hasNext())
		{
			graph::Statement *statement = iter.next();

			if (graph::Variable *variable = dynamic_cast<graph::Variable*>(statement))
			{
				Variable::createVar(body, *variable);
			}
			else if (graph::ControlStructure *control = dynamic_cast<graph::ControlStructure*>(statement))
			{
				ControlStructure structure(body, *control);
			}
			else if (graph::Function *function = dynamic_cast<graph::Function*>(statement))
			{
				//Function function(*body, *function);
			}
			else
			{
				body.append("\t" + statement->verbatim());
			}
		}


		body.append("}");
	}
}}