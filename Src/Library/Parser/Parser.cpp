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
		parseStatement_block(0);

		return true;
	}


	bool Parser::isFunctionDeclaration(const QString &line)
	{
		return line == "int main()";
	}


	int Parser::parseStatement_preprocessor(int index)
	{
		//TODO for now we will assume all preprocessor statements are 1 liners
		mCurrentGraph.rootBlock().appendStatement(graph::Preprocessor(mLineBuffer[index]));
		return index;
	}


	int Parser::parseStatement_function(int index)
	{
		//if next line is an opening brace, it must be a block
		if (mLineBuffer[++index] == "{")
		{
			index = parseStatement_block(++index);
		}

		return index;
	}


	int Parser::parseStatement_block(int index)
	{
		QString& line = mLineBuffer[index];

		// Statement : Preprocessor
		if (line.startsWith("#"))
		{
			index = parseStatement_preprocessor(index);
		}

		// Statement : Function
		else if (isFunctionDeclaration(line))
		{
			index = parseStatement_function(index);
		}

		return index;
	}
}}