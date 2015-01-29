//==================================================================================================================|
// Created 2015.01.29 by Daniel L. Watkins
//
// Copyright (C) 2015 Valpineware
// This file is licensed under the MIT License.
//==================================================================================================================|

#ifndef _vc_parser_Parser_h
#define _vc_parser_Parser_h

#include <Library.h>
#include <Graph/Graph.h>

namespace vc { namespace parser
{
	/**
	 * @brief Builds a source graph from a raw Valpine file.
	 */
	class Parser
	{
	public:
		graph::Graph parseFile(const QString &filepath);
	};
}}

#endif
