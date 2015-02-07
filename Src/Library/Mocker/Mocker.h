//==================================================================================================================|
// Created 2015.01.29 by Daniel L. Watkins
//
// Copyright (C) 2015 Valpineware
// This file is licensed under the MIT License.
//==================================================================================================================|

#ifndef _vc_mocker_Mocker_h
#define _vc_mocker_Mocker_h

#include <Graph/Graph.h>
#include <Library.h>

namespace vc { namespace mocker
{
	struct StatementTypes
	{
		graph::Preprocessor* preprocessor;
		graph::Function* function;
		graph::Statement* statement;
	};

	/**
	 * @brief Mocks a Valpine source graph as C++.
	 */
	class Mocker
	{
	private:
		const graph::Graph* graph;
		StatementTypes types;

		void buildFunction(QVector<QString>& program, graph::Function& function);
		void processBlock(QVector<QString>& program, QListIterator<graph::Statement*>& iter);

	public:
		Mocker() {};
		void mock(const graph::Graph &graph);
		QString outputFilepath() const { return ""; }
		QVector<QString> buildList();
	};
}}

#endif
