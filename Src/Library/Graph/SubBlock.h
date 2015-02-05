//==================================================================================================================|
// Created 2015.02.05 by Daniel L. Watkins
//
// Copyright (C) 2015 Valpineware
// This file is licensed under the MIT License.
//==================================================================================================================|

#ifndef _vc_graph_SubBlock_h
#define _vc_graph_SubBlock_h

#include "Block.h"

namespace vc { namespace graph
{
	/**
	 * @brief 
	 */
	class SubBlock : public Statement
	{
	public:
		SubBlock(const QString &verbatim) : Statement(verbatim) {}

		Block& block() { return mBlock; }
		const Block& block() const { return mBlock; }

	private:
		Block mBlock;
	};
}}

#endif
