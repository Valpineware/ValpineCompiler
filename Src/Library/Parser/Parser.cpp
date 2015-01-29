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
			mLineBuffer.append(textStream.readLine());

		parseLineBuffer();

		return true;
	}


	void Parser::parseLineBuffer()
	{
		for (int i=0; i<mLineBuffer.count(); i++)
		{
			QString& line = mLineBuffer[i];

			// Statement : Preprocessor
			if (line.startsWith("#"))
			{
				i = parseStatement_preprocessor(i);
			}

			// Statement : Function
			else if (isFunctionDeclaration(line))
			{
				i = parseStatement_function(i);
			}
		}
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
		if (mLineBuffer[index] == "{")
		{
			index = parseStatement_block(index);
		}

		return index;
	}


	int Parser::parseStatement_block(int index)
	{
		return index;
	}
}}