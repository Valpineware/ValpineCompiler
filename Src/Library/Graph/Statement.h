//==================================================================================================================|
// Created 2015.01.29 by Daniel L. Watkins
//
// Copyright (C) 2015 Valpineware
// This file is licensed under the MIT License.
//==================================================================================================================|

#include <Library.h>

#ifndef _vc_graph_Statement_h
#define _vc_graph_Statement_h

namespace vc { namespace graph
{
	enum class ScopeType
	{
		Root,
		ExecutionBlock,
		ClassBlock
	};


	/**
	 * @brief A base class for representing a statement in Valpine. It could be a declaration, function call, etc.
	 */
	class Statement
	{
	public:
		virtual ~Statement() {}

		Statement() = delete;
		Statement(const QString &verbatim) : mVerbatim(verbatim.trimmed()) { }

		/**
		 * @returns the statement as a string as it appeared in the Valpine source file.
		 */
		QString verbatim() const { return mVerbatim; }

	private:
		QString mVerbatim;
	};
}}

#endif
