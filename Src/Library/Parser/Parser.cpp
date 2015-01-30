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


	bool Parser::isFunctionDeclaration(const QString &line)
	{
		return line == "int main()";
	}

	
	bool Parser::isBlankLine(const QString &line)
	{
		QString verify = line;
		verify.replace("\t", "");
		verify.replace(" ", ""); 
		verify.replace("\n", "");

		return verify == "";

		//TODO this method is unreliable when other whitespace characters are present
	}


	int Parser::parseStatement_preprocessor(int index, graph::Block &parent)
	{
		//TODO for now we will assume all preprocessor statements are 1 liners
		parent.appendStatement(new graph::Preprocessor(mLineBuffer[index]));
		return index;
	}


	int Parser::parseStatement_function(int index, graph::Block &parent)
	{
		graph::Function *func = new graph::Function(mLineBuffer[index]);
		parent.appendStatement(func);

		//if next line is an opening brace, it must be a block
		if (mLineBuffer[++index] == "{")
		{
			index = parseStatement_block(++index, &func->block());
		}

		return index;
	}


	int Parser::parseStatement_block(int index, graph::Block *host)
	{
		while (index < mLineBuffer.count()  &&  mLineBuffer[index] != "}")
		{
			QString& line = mLineBuffer[index];

			// Statement : Preprocessor
			if (line.startsWith("#"))
			{
				index = parseStatement_preprocessor(index, *host);
			}

			// Statement : Function
			else if (isFunctionDeclaration(line))
			{
				index = parseStatement_function(index, *host);
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