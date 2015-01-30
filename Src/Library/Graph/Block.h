//==================================================================================================================|
// Created 2015.01.29 by Daniel L. Watkins
//
// Copyright (C) 2015 Valpineware
// This file is licensed under the MIT License.
//==================================================================================================================|

#ifndef _vc_graph_Block_h
#define _vc_graph_Block_h

#include <Library.h>
#include "Statement.h"

namespace vc { namespace graph
{
	/**
	 * @brief Represents the body of a generic block (global block, function, class definition, while body, etc.).
	 */
	class Block : public Statement
	{
	public:
		Block() : Statement("") {}

		~Block()
		{
			for (Statement* s : mStatements)
				delete s;
		}

		void appendStatement(Statement* statement) { mStatements.append(statement); }
		const QList<Statement*>& statements() const { return mStatements; }

	private:
		QList<Statement*> mStatements;
	};
}}

#endif
