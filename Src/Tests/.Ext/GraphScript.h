//==================================================================================================================|
// Created 2015.02.28 by Daniel L. Watkins
//
// Copyright (C) 2015 Valpineware
// This file is licensed under the MIT License.
//==================================================================================================================|

#ifndef _test_ext_ParseScript_H
#define _test_ext_ParseScript_H

#include "../Tests.h"
#include <Graph/Graph.h>
using namespace vc::graph;

namespace ext
{
	/**
	 * Utility that constructs an in-memory graph instance from .gs files.
	 */
	class GraphScript
	{
	public:
		bool parse(const QString &filepath);

		const Graph& graph() const { return mGraph; }
		Graph& graph() { return mGraph; }

	private:
		bool parseLine(const QString &line, int lineNumber);
		void applyStatement(int indentation, const QStringRef &keyword, const QStringRef &verbatim);

		Graph mGraph;
		QVector<Statement*> mPreviousStatementTiers;
		Class::AccessType mCurrentAccessType;
	};
};

#endif
