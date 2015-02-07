//==================================================================================================================|
// Created 2015.02.02 by Daniel L. Watkins
//
// Copyright (C) 2015 Valpineware
// This file is licensed under the MIT License.
//==================================================================================================================|

#ifndef _vc_graph_ControlStructure_h
#define _vc_graph_ControlStructure_h

#include "SubBlock.h"

namespace vc { namespace graph
{
	/**
	 * @brief 
	 */
	class ControlStructure : public SubBlock
	{
	public:
		ControlStructure(const QString &verbatim) : SubBlock(verbatim) {}

		static ControlStructure* createFromVerbatimSignature(const QString signature);

		void setName(const QString &name) { mName = name; }
		QString name() const { return mName; }

		void setExpression(const QString &expression) { mExpression = expression; }
		QString expression() const { return mExpression; }

	private:
		QString mName, mExpression;
	};
}}

#endif
