//==================================================================================================================|
// Created 2015.01.29 by Daniel L. Watkins
//
// Copyright (C) 2015 Valpineware
// This file is licensed under the MIT License.
//==================================================================================================================|

#include "Mocker.h"

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
		buildBlock(buffer, rootBlock);
	}


	void Mocker::buildFunction(QVector<QString> &program, graph::Function &function)
	{
		//build opening experssion
		QString functionDef = function.returnType().fullType() + " " + function.id() + "(";
		
		//add in the parameters
		const QVector<graph::Parameter> &param = function.parameters();
		for (int i = 0; i < param.size(); i++)
		{
			functionDef += param[i].type.fullType() + " " + param[i].id;

			if ((i + 1) != param.size())
			{
				functionDef += ", ";
			}
		}

		functionDef += ")";
		program.append(functionDef);

		program.append("{");

		buildBlock(program, function.block());

		program.append("}");
	}


	void Mocker::buildBlock(QVector<QString> &program, const graph::Block &block)
	{
		QListIterator<graph::Statement*> iter(block.statements());

		while (iter.hasNext())
		{
			graph::Statement *statement = iter.next();

			if (graph::Preprocessor *preprocessor = dynamic_cast<graph::Preprocessor*>(statement))
			{
				program.append(preprocessor->verbatim());
			}
			else if (graph::Function *function = dynamic_cast<graph::Function*>(statement))
			{
				buildFunction(program, *function);
			}
			else
			{
				program.append(statement->verbatim());
			}
		}
	}
}}