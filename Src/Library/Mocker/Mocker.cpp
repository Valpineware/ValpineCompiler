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
		buildBlock(graph.block(), false);		

		QTextStream outStream(&outputDevice);
		for (const QString &line : includes)
		{
			outStream << line << "\n";
		}

		for (const QString &line : forwardDeclartions)
		{
			outStream << line << "\n";
		}

		for (const QString &line : body)
		{
			outStream << line << "\n";
		}
	}


	void Mocker::buildBlock(const graph::Block &block, bool writeBraces)
	{
		QListIterator<graph::Statement*> iter(block.statements());

		if (writeBraces)
		{
			body.append("{");
		}

		while (iter.hasNext())
		{
			graph::Statement *statement = iter.next();

			if (graph::Preprocessor *preprocessor = dynamic_cast<graph::Preprocessor*>(statement))
			{
				includes.append(preprocessor->verbatim());
			}
			else if (graph::Function *function = dynamic_cast<graph::Function*>(statement))
			{
				Function* newFunction = new Function(*function);

				if (function->id() != "main")
				{
					forwardDeclartions.append(newFunction->declartion() + ";");
				}
				
				body.append(newFunction->declartion());
				delete newFunction;

				buildBlock(function->block());
			}
			else
			{
				body.append(statement->verbatim());
			}
		}

		if (writeBraces)
		{
			body.append("}");
		}
	}
}}