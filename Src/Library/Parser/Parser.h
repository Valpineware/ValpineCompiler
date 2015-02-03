//==================================================================================================================|
// Created 2015.01.29 by Daniel L. Watkins
//
// Copyright (C) 2015 Valpineware
// This file is licensed under the MIT License.
//==================================================================================================================|

#ifndef _vc_parser_Parser_h
#define _vc_parser_Parser_h

#include <Library.h>
#include <Graph/Graph.h>

namespace vc { namespace parser
{
	/**
	 * @brief Builds a source graph from a raw Valpine file.
	 */
	class Parser
	{
	public:
		bool parseFile(const QString &filepath);

		graph::Graph& graph() { return mCurrentGraph; }	//TODO these two lines are a pain to have to do in C++
		const graph::Graph& graph() const { return mCurrentGraph; }	//let's find a way to eliminate this in Valpine

	private:
		graph::Graph mCurrentGraph;
		QVector<QString> mLineBuffer;

		void parseLineBuffer();

		bool isBlankLine(const QString &line);

		/**
		 * The following methods return an integer indicating the line where the entire statement ended.
		 * For function declarations, the return value is equal to the line index for the closing brace.
		 * The input parameter line is the index position for the line where the statment starts.
		 */
		 
		int parseStatement_preprocessor(int index, graph::Block &parent);
		int Parser::parseStatement_subBlock(int index, graph::Block &block);
		int parseStatement_block(int index, graph::Block *host);
	};
}}

#endif
