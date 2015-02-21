//==================================================================================================================|
// Created 2015.02.19 by John Koehn
//
// Copyright (C) 2015 Valpineware
// This file is licensed under the MIT License.
//==================================================================================================================|

#include "ControlStructure.h"
#include "Variable.h"

namespace vc { namespace mocker
{
	//TODO ADD DEPTH LEVEL FOR INTERNAL TABBING
	ControlStructure::ControlStructure(QVector<QString> &body, graph::ControlStructure &controlStructure)
	{
		mBody = &body;
		mControlStructure = &controlStructure;

		buildStatement();
		buildBody();
	}


	void ControlStructure::buildStatement()
	{
		QString statement = mControlStructure->name() + "(" + mControlStructure->expression() + ")";
		mBody->append(statement);
	}


	void ControlStructure::buildBody()
	{
		QListIterator<graph::Statement*> iter(mControlStructure->block().statements());

		mBody->append("{");

		while (iter.hasNext())
		{
			graph::Statement *statement = iter.next();

			if (graph::Variable *variable = dynamic_cast<graph::Variable*>(statement))
			{
				Variable::createVar(*mBody, *variable);
			}
			else if (graph::ControlStructure *control = dynamic_cast<graph::ControlStructure*>(statement))
			{
				ControlStructure(*mBody, *control);
			}
			else
			{
				mBody->append("\t" + statement->verbatim());
			}
		}


		mBody->append("}");
	}
}}