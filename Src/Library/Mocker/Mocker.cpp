//==================================================================================================================|
// Created 2015.01.29 by Daniel L. Watkins
//
// Copyright (C) 2015 Valpineware
// This file is licensed under the MIT License.
//==================================================================================================================|

#include "Mocker.h"

namespace vc { namespace mocker
{
	void Mocker::mock(const graph::Graph &graph)
	{
		this->graph = &graph;
	}

	QVector<QString> Mocker::buildList()
	{
		const graph::Block &root = graph->block();
		QVector<QString> program;

		QListIterator<graph::Statement*> iter(root.statements());

		graph::Preprocessor* preprocessor;
		graph::Function* function;
		graph::Statement* statement;

		while (iter.hasNext())
		{
			statement = iter.next();

			//check the type of this statement
			preprocessor = dynamic_cast<graph::Preprocessor*> (statement);
			if (preprocessor != NULL)
			{
				program.append(preprocessor->verbatim());
			}
			else if ((function = dynamic_cast<graph::Function*>(statement)) != NULL)
			{
				buildFunction(program, *function);
			}
		}

		return program;
	}


	void Mocker::buildFunction(QVector<QString>& program, graph::Function& function)
	{
		/*program.append(function.verbatim());
		program.append("{");

		QListIterator<graph::Statement*> iter(program.);*/
	}

}}