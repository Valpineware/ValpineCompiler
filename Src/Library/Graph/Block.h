//==================================================================================================================|
// Created 2015.01.29 by Daniel L. Watkins
//
// Copyright (C) 2015 Valpineware
// This file is licensed under the MIT License.
//==================================================================================================================|

#include <Library.h>
#include "Statement.h"

#ifndef _vc_graph_Block_h
#define _vc_graph_Block_h

namespace vc { namespace graph
{
	/**
	 * @brief Represents the body of a generic block (global block, function, class definition, while body, etc.).
	 */
	class Block
	{
	public:
		void appendStatement(const Statement &statement) { mStatements.append(statement); }
		QListIterator<Statement> statementIterator() { return QListIterator<Statement>(mStatements); }

	private:
		QList<Statement> mStatements;
	};
}}

#endif
