//==================================================================================================================|
// Created 2015.01.29 by Daniel L. Watkins
//
// Copyright (C) 2015 Valpineware
// This file is licensed under the MIT License.
//==================================================================================================================|

#include "Parser.h"

namespace vc { namespace parser
{
	bool Parser::parseFile(const QString &filepath)
	{
		mCurrentGraph = graph::Graph();
		QFile file(filepath);

		if (!file.open(QIODevice::ReadOnly))
			return false;

		QTextStream textStream(&file);
		while (!textStream.atEnd())
		{
			QString line = textStream.readLine();
			mLineBuffer.append(line);
		}

		//parse the global block (entire file) starting at line 0
		parseStatement_block(0, &mCurrentGraph.block());

		return true;
	}

	
	bool Parser::isBlankLine(const QString &line)
	{
		return graph::Statement(line).verbatim() == "";
	}


	int Parser::parseStatement_preprocessor(int index, graph::Block &parent)
	{
		//TODO for now we will assume all preprocessor statements are 1 liners
		parent.appendStatement(new graph::Preprocessor(mLineBuffer[index]));
		return index;
	}


	int Parser::parseStatement_subBlock(int index, graph::Block &block)
	{
		//if next line is an opening brace, it must be a block
		if (QRegExp("\\s*\\{\\s*").exactMatch(mLineBuffer[++index]))
		{
			index = parseStatement_block(++index, &block);
		}

		return index;
	}


	int Parser::parseStatement_block(int index, graph::Block *host)
	{
		while (index < mLineBuffer.count()  &&  !QRegExp("\\s*\\}\\s*").exactMatch(mLineBuffer[index]))//mLineBuffer[index] != "}")
		{
			QString& line = mLineBuffer[index];

			// Statement : Preprocessor
			if (line.startsWith("#"))
			{
				index = parseStatement_preprocessor(index, *host);
			}

			// Statement : Function
			else if (graph::Function *f = graph::Function::createFromVerbatimSignature(line))
			{
				host->appendStatement(f);
				index = parseStatement_subBlock(index, f->block());
			}

			// Statement : ControlStructure
			else if (graph::ControlStructure *cs = graph::ControlStructure::createFromVerbatimSignature(line))
			{
				host->appendStatement(cs);
				index = parseStatement_subBlock(index, cs->block());
			}

			// Blank line
			else if (isBlankLine(line))
			{
				//do nothing
			}


			// Statement : Regular
			else
			{
				host->appendStatement(new graph::Statement(line));
			}

			index++;
		}

		return index;
	}
}}