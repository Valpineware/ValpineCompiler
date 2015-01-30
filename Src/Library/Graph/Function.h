//==================================================================================================================|
// Created 2015.01.29 by Daniel L. Watkins
//
// Copyright (C) 2015 Valpineware
// This file is licensed under the MIT License.
//==================================================================================================================|

#include <Library.h>

#include "Statement.h"
#include "Block.h"

#ifndef _vc_graph_Function_h
#define _vc_graph_Function_h

namespace vc { namespace graph
{
	/**
	 * @brief Represents the body of a function of control structure that is executed.
	 */
	class Function : public Statement
	{
	public:
		Function() = delete;

		Function(const QString &verbatim) : Statement(verbatim) {}

		Block& block() { return mBlock; }
		const Block& block() const { return mBlock; }

	private:
		Block mBlock;
	};
}}

#endif
