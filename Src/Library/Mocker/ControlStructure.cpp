//==================================================================================================================|
// Created 2015.02.19 by John Koehn
//
// Copyright (C) 2015 Valpineware
// This file is licensed under the MIT License.
//==================================================================================================================|

#include "ControlStructure.h"
#include "Variable.h"

namespace vc { namespace mocker {

	//TODO ADD DEPTH LEVEL FOR INTERNAL TABBING
	ControlStructure::ControlStructure(QVector<QString> &body, graph::ControlStructure &controlStatement)
	{
		buildStatement(body, controlStatement);
		buildBody(body, controlStatement);
	}

	void ControlStructure::buildStatement(QVector<QString> &body, graph::ControlStructure &controlStatement)
	{
		QString statement = controlStatement.name() + "(" + controlStatement.expression() + ")";
		body.append(statement);
	}

	void ControlStructure::buildBody(QVector<QString> &body, graph::ControlStructure & controlStatement)
	{
		QListIterator<graph::Statement*> iter(controlStatement.block().statements());

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
				ControlStructure(body, *control);
			}
			else
			{
				body.append("\t" + statement->verbatim());
			}
		}


		body.append("}");
	}
	

}}