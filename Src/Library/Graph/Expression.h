//==================================================================================================================|
// Created 2015.02.20 by Daniel L. Watkins
//
// Copyright (C) 2015 Valpineware
// This file is licensed under the MIT License.
//==================================================================================================================|

#ifndef _vc_graph_Expression_h
#define _vc_graph_Expression_h

#include "Statement.h"

namespace vc { namespace graph
{
	/**
	 * @brief
	 */
	class Expression : public Statement
	{
	public:
		Expression(const QString &verbatim) : Statement(verbatim) {}

		static Expression* createFromVerbatimSignature(const QString signature);

		struct Component
		{
		};

		
		const QList<Component*> components() const { return mComponents; }

	private:
		QList<Component*> mComponents;
	};
}}

#endif
