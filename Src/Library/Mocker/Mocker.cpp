//==================================================================================================================|
// Created 2015.01.29 by Daniel L. Watkins
//
// Copyright (C) 2015 Valpineware
// This file is licensed under the MIT License.
//==================================================================================================================|

#include "Mocker.h"

namespace vc { namespace mocker
{
	Mocker::Mocker(const graph::Graph &graph)
	{
		this->graph = graph;
		run();
	}

	int Mocker::run()
	{
		graph::Block &root = graph.block();

		//traverse through the statements
		QListIterator<graph::Statement*> iter(root.statements());

		int count = 0;
		while (iter.hasNext())
		{
			iter.next();
			count++;
		}

		return count;
	}

}}