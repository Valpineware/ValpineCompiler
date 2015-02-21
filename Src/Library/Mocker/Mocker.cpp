//==================================================================================================================|
// Created 2015.01.29 by Daniel L. Watkins
//
// Copyright (C) 2015 Valpineware
// This file is licensed under the MIT License.
//==================================================================================================================|

#include "Mocker.h"
#include "Function.h"
#include "Variable.h"

namespace vc { namespace mocker
{
	void Mocker::mock(const graph::Graph &graph, QIODevice &outputDevice)
	{
		buildBlock(graph.block());		

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


	void Mocker::buildBlock(const graph::Block &block)
	{
		QListIterator<graph::Statement*> iter(block.statements());

		while (iter.hasNext())
		{
			graph::Statement *statement = iter.next();

			if (graph::Preprocessor *preprocessor = dynamic_cast<graph::Preprocessor*>(statement))
			{
				includes.append(preprocessor->verbatim());
			}
			else if (graph::Function *function = dynamic_cast<graph::Function*>(statement))
			{
				createFunction(*function);
			}
			else if (graph::Variable *variable = dynamic_cast<graph::Variable*>(statement)) // --happens with only global variables
			{
				Variable::createVar(body, *variable);
			}
			else
			{
				body.append(statement->verbatim());
			}
		}
	}

	void Mocker::createFunction(graph::Function &function)
	{
		Function newFunction(body, forwardDeclartions, function);

		//get nested functions and build them
		QQueue<graph::Function*> &nestedFunctions = newFunction.nestedFunctions();

		while (!nestedFunctions.isEmpty())
		{
			//build the nested function and add any new nested functions to the end of the queue
			Function nestedFunction(body, forwardDeclartions, *nestedFunctions.dequeue());
			nestedFunctions.append(nestedFunction.nestedFunctions());
		}
	}

}}