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
#include "DeclarationBlock.h"

namespace vc { namespace mocker
{
	DeclarationBlock::DeclarationBlock(QVector<QString> &body, QVector<QString> &forwardDecs, const graph::Function &function, int scope)
	{
		mData.body = &body;
		mData.forwardDecs = &forwardDecs;
		mData.scope = scope;
		mData.functions = new QQueue<const graph::Function*>;
		mData.functions->enqueue(&function);

		createFunction();
	}


	void DeclarationBlock::buildBlock(const graph::Block &block, FileData &data)
	{
		QListIterator<graph::Statement*> iter(block.statements());
		data.body->append(Utility::createTabs(data.scope) + "{");

		//increase scope level
		data.scope += 1;

		while (iter.hasNext())
		{
			graph::Statement *statement = iter.next();

			if (graph::Variable *variable = dynamic_cast<graph::Variable*>(statement))
			{
				Variable::createVar(*(data.body), *variable, data.scope);
			}
			else if (graph::ControlStructure *control = dynamic_cast<graph::ControlStructure*>(statement))
			{
				ControlStructure structure(*control, data);
			}
			else if (graph::Function *function = dynamic_cast<graph::Function*>(statement))
			{
				data.functions->enqueue(function);
			}
			else if (graph::Preprocessor *preprocessor = dynamic_cast<graph::Preprocessor*>(statement))
			{
				data.body->append(Utility::createTabs(data.scope) + preprocessor->verbatim());
			}
			else
			{ 
				data.body->append(Utility::createTabs(data.scope) + statement->verbatim());
			}
		}

		data.scope -= 1;
		data.body->append(Utility::createTabs(data.scope) + "}");
	}

	void DeclarationBlock::createFunction()
	{
		Function newFunction(mData);

		while (!mData.functions->isEmpty())
		{
			//build the nested function and add any new nested functions to the end of the queue
			Function nestedFunction(mData);
		}
	}
}}