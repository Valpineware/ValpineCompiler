//==================================================================================================================|
// Created 2015.01.29 by Daniel L. Watkins
//
// Copyright (C) 2015 Valpineware
// This file is licensed under the MIT License.
//==================================================================================================================|

#ifndef _vc_graph_Preprocessor_h
#define _vc_graph_Preprocessor_h

#include "Statement.h"

namespace vc { namespace graph
{
	/**
	 * @brief An in-memory representation of a Valpine source file using a graph like data structure.
	 */
	class Preprocessor : public Statement
	{
		//nothing yet. Just want to represent this as a preprocessor statement
	public:
		Preprocessor(const QString &verbatim) { setVerbatim(verbatim); }
	};
}}

#endif
