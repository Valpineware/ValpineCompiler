//==================================================================================================================|
// Created 2015.02.06 by Daniel L. Watkins
//
// Copyright (C) 2015 Valpineware
// This file is licensed under the MIT License.
//==================================================================================================================|

#ifndef _vc_graph_Variable_h
#define _vc_graph_Variable_h

#include "Statement.h"
#include "TypeExpression.h"

namespace vc { namespace graph
{
	/**
	 * @brief Declaration of a variable (including ivars) with an optional initialization clause.
	 */
	class Variable : public Statement
	{
	public:
		Variable(const QString &verbatim) : Statement(verbatim) {}

		static Variable* createFromVerbatimSignature(const QString signature);

		void setTypeExpression(const TypeExpression &typeExpression) { mTypeExpression = typeExpression; }
		const TypeExpression& typeExpression() const { return mTypeExpression; }
		void setId(const QString &id) { mId = id; }
		QString id() const { return mId; }
		void setInitExpression(const QString &initExpression) { mInitExpression = initExpression; }
		QString initExpression() const { return mInitExpression; }

	private:
		TypeExpression mTypeExpression;
		QString mId, mInitExpression;
	};
}}

#endif
