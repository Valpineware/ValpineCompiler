//==================================================================================================================|
// Created 2015.01.29 by Daniel L. Watkins
//
// Copyright (C) 2015 Valpineware
// This file is licensed under the MIT License.
//==================================================================================================================|

#include <Library.h>
#include <Graph/Graph.h>

namespace vc { namespace parser
{
	class Parser
	{
	public:
		graph::Graph parseFile(const QString &filepath);
	};
}}