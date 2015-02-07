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

		processBlock(program, iter);

		return program;
	}


	void Mocker::buildFunction(QVector<QString>& program, graph::Function& function)
	{
		program.append(function.verbatim());
		program.append("{");

		QListIterator<graph::Statement*> iter(function.block().statements());

		processBlock(program, iter);

		program.append("}");
	}


	void Mocker::processBlock(QVector<QString>& program, QListIterator<graph::Statement*>& iter)
	{

		while (iter.hasNext())
		{
			types.statement = iter.next();

			types.preprocessor = dynamic_cast<graph::Preprocessor*> (types.statement);
			if (types.preprocessor != NULL)
			{
				program.append(types.preprocessor->verbatim());
			}
			else if ((types.function = dynamic_cast<graph::Function*>(types.statement)) != NULL)
			{
				buildFunction(program, *(types.function));
			}
			else
			{
				program.append(types.statement->verbatim());
			}
		}
	}

}}