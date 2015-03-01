//==================================================================================================================|
// Created 2015.01.29 by Daniel L. Watkins
//
// Copyright (C) 2015 Valpineware
// This file is licensed under the MIT License.
//==================================================================================================================|

#include "Mocker.h"
#include "DeclarationBlock.h"
#include "Variable.h"
#include "Utility.h"

namespace vc { namespace mocker
{
	void Mocker::mock(const graph::Graph &graph, QIODevice &outDevice_Implementation, QIODevice &outDevice_Header)
	{
		buildBlock(graph.block());		

		QTextStream outStream(&outDevice_Implementation);
		for (const QString &line : mIncludes)
		{
			outStream << line << "\n";
		}

		//TODO, move to header file
		for (const QString &line : mForwardDecs)
		{
			outStream << line << "\n";
		}

		for (const QString &line : mBody)
		{
			outStream << line << "\n";
		}

		outStream.setDevice(&outDevice_Header);
		for (const QString &line : mHeader)
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
				mIncludes.append(preprocessor->verbatim());
			}
			else if (graph::Function *function = dynamic_cast<graph::Function*>(statement))
			{
				//go into deceleration block
				DeclarationBlock decBlock(mBody, mForwardDecs, *function, mScope);
			}
			else if (graph::Variable *variable = dynamic_cast<graph::Variable*>(statement)) // --happens with only global variables
			{
				Variable::createVar(mBody, *variable, mScope);
			}
			else
			{
				mBody.append(Utility::createTabs(mScope) + statement->verbatim());
			}
		}
	}



}}