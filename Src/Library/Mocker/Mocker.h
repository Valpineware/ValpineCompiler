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
	/**
	 * @brief Mocks a Valpine source graph as C++.
	 */
	class Mocker
	{
	private:
		void buildList(QVector<QString> &buffer, const graph::Block &rootBlock);
		void buildBlock(QVector<QString> &buffer, const graph::Block &block, bool writeBraces = true);

	public:
		Mocker() {};
		void mock(const graph::Graph &graph, QIODevice& outputDevice);
	};
}}

#endif
