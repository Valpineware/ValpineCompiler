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
		static ControlStructure* make(const QString signature);

		QString name() const;

		const QList<Statement*> expressionList() const { return mExpression; }
		QString expression() const;

	private:
		ControlStructure(const QString &verbatim) : SubBlock(verbatim) {}

		void parseAndAssignExpression(const QString &verbatim);

		QVector<QString> mKeywords;
		QList<Statement*> mExpression;
	};
}}

#endif
