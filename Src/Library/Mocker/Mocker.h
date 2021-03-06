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
#include "Header.h"

namespace vc { namespace mocker
{
	struct MockerData
	{
		QVector<QString> includes;
		QVector<QString> body;

		Header header;
		
		int scope = 0;
	};

	/**
	 * @brief Mocks a Valpine source graph as C++.
	 */
	class Mocker
	{
	private:
		void buildBlock(const graph::Block &block);
		void createVar(graph::Variable &var);

		
		MockerData mData;

	public:
		Mocker() {};
		void mock(const graph::Graph &graph, QIODevice &outDevice_Implementation, QIODevice &outDevice_Header);
	};
}}

#endif
