//==================================================================================================================|
// Created 2015.02.02 by Daniel L. Watkins
//
// Copyright (C) 2015 Valpineware
// This file is licensed under the MIT License.
//==================================================================================================================|

#ifndef _vc_graph_ControlStructure_h
#define _vc_graph_ControlStructure_h

#include "Statement.h"
#include "Block.h"

namespace vc { namespace graph
{
	/**
	 * @brief 
	 */
	class ControlStructure : public Statement
	{
	public:
		ControlStructure(const QString &verbatim) : Statement(verbatim) {}

		void setName(const QString &name) { mName = name; }
		QString name() const { return mName; }

		void setExpression(const QString &expression) { mExpression = expression; }
		QString expression() const { return mExpression; }

		Block& block() { return mBlock; }
		const Block& block() const { return mBlock; }

	private:
		QString mName, mExpression;
		Block mBlock;
	};
}}

#endif
