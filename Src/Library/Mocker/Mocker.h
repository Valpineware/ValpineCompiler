//==================================================================================================================|
// Created 2015.01.29 by Daniel L. Watkins
//
// Copyright (C) 2015 Valpineware
// This file is licensed under the MIT License.
//==================================================================================================================|

#ifndef _vc_mocker_Mocker_h
#define _vc_mocker_Mocker_h

#include <Graph/Graph.h>

namespace vc { namespace mocker
{
	/**
	 * @brief Mocks a Valpine source graph as C++.
	 */
	class Mocker
	{
	private:
		graph::Graph graph;

	public:
		Mocker(const graph::Graph &graph);
		QString outputFilepath() const { return ""; }
		graph::Graph getGraph() { return graph; }
		int run();
	};
}}

#endif
