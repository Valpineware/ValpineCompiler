//==================================================================================================================|
// Created 2015.02.20 by John Koehn
//
// Copyright (C) 2015 Valpineware
// This file is licensed under the MIT License.
//==================================================================================================================|

#include "Utility.h"
#include "Variable.h"
#include "ControlStructure.h"
#include "Function.h"
#include "DecelerationBlock.h"

namespace vc { namespace mocker
{
	DecelerationBlock::DecelerationBlock(QVector<QString> &body, QVector<QString> &forwardDecs, const graph::Function &function, int scope)
	{
		mBody = &body;
		mForwardDecs = &forwardDecs;
		mScope = scope;

		createFunction(function, *mBody, *mForwardDecs, mScope);
	}

	void DecelerationBlock::buildBlock(const graph::Block &block, Data &data)
	{
		QListIterator<graph::Statement*> iter(block.statements());
		data.body->append("{");

		//increase scope level
		data.scope += 1;

		while (iter.hasNext())
		{
			graph::Statement *statement = iter.next();

			if (graph::Variable *variable = dynamic_cast<graph::Variable*>(statement))
			{
				Variable::createVar(*(data.body), *variable);
			}
			else if (graph::ControlStructure *control = dynamic_cast<graph::ControlStructure*>(statement))
			{
				ControlStructure structure(*control, data);
			}
			else if (graph::Function *function = dynamic_cast<graph::Function*>(statement))
			{
				data.nestedFunctions->enqueue(function);
			}
			else
			{
				data.body->append("\t" + statement->verbatim());
			}
		}


		data.body->append("}");
	}

	void DecelerationBlock::createFunction(const graph::Function &function, QVector<QString> &body, QVector<QString> &forwardDecs, int scope)
	{
		Function newFunction(body, forwardDecs, function, scope);

		//get nested functions and build them
		QQueue<graph::Function*> &nestedFunctions = newFunction.nestedFunctions();

		while (!nestedFunctions.isEmpty())
		{
			//build the nested function and add any new nested functions to the end of the queue
			Function nestedFunction(body, forwardDecs, *nestedFunctions.dequeue(), scope);
			nestedFunctions.append(nestedFunction.nestedFunctions());
		}
	}
}}