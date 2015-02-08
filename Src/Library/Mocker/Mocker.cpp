//==================================================================================================================|
// Created 2015.01.29 by Daniel L. Watkins
//
// Copyright (C) 2015 Valpineware
// This file is licensed under the MIT License.
//==================================================================================================================|

#include "Mocker.h"
#include "Function.h"

namespace vc { namespace mocker
{
	void Mocker::mock(const graph::Graph &graph, QIODevice &outputDevice)
	{
		QVector<QString> buffer;
		buildList(buffer, graph.block());		

		QTextStream outStream(&outputDevice);
		for (const QString &line : buffer)
		{
			outStream << line << "\n";
		}
	}


	void Mocker::buildList(QVector<QString> &buffer, const graph::Block &rootBlock)
	{
		buildBlock(buffer, rootBlock, false);
	}


	void Mocker::buildBlock(QVector<QString> &buffer, const graph::Block &block, bool writeBraces)
	{
		QListIterator<graph::Statement*> iter(block.statements());

		if (writeBraces)
		{
			buffer.append("{");
		}

		while (iter.hasNext())
		{
			graph::Statement *statement = iter.next();

			if (graph::Preprocessor *preprocessor = dynamic_cast<graph::Preprocessor*>(statement))
			{
				buffer.append(preprocessor->verbatim());
			}
			else if (graph::Function *function = dynamic_cast<graph::Function*>(statement))
			{
				Function* newFunction = new Function(*function);
				buffer.append(newFunction->declartion());
				delete newFunction;

				buildBlock(buffer, function->block());
			}
			else
			{
				buffer.append(statement->verbatim());
			}
		}

		if (writeBraces)
		{
			buffer.append("}");
		}
	}
}}