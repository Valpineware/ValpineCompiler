//==================================================================================================================|
// Created 2015.02.28 by Daniel L. Watkins
//
// Copyright (C) 2015 Valpineware
// This file is licensed under the MIT License.
//==================================================================================================================|

#include "ParseScript.h"

namespace ext
{
	bool ParseScript::parse(const QString &filepath)
	{
		mGraph = Graph();
		mPreviousStatementTiers.push_back(&mGraph.block());

		QFile file(filepath);

		if (!file.open(QIODevice::ReadOnly))
			return false;

		QTextStream textStream(&file);
		int lineNumber = 0;
		while (!textStream.atEnd())
		{
			parseLine(textStream.readLine(), lineNumber++);
		}

		return true;
	}


	bool ParseScript::parseLine(const QString &line, int lineNumber)
	{
		//each leading tab increases the level
		int indentation = 0;
		int lastLeadingTab = 0;
		for (int i=0; i<line.count(); i++)
		{
			if (line[i] == "\t")
				indentation++;
			else
			{
				lastLeadingTab = i;
				break;
			}
		}

		//figure out the keyword
		int space = line.indexOf(QRegExp("[\t ]"), lastLeadingTab+1);
		if (space == -1)
		{
			qDebug() << "ParseScript: Error parsing line " << lineNumber;
			return false;
		}

		QStringRef keyword = line.midRef(lastLeadingTab, space-lastLeadingTab);
		QStringRef verbatim = line.rightRef(line.count()-space-1);
		applyStatement(indentation, keyword, verbatim);

		return true;
	}


	void ParseScript::applyStatement(int indentation, const QStringRef &keyword, const QStringRef &verbatim)
	{
		Statement *statement = nullptr;

		if (keyword == "STATE")
			statement = new Statement(verbatim.toString());
		else if (keyword == "CLASS")
			statement = Class::make(verbatim.toString());
		else if (keyword == "CONTROL")
			statement = ControlStructure::make(verbatim.toString());
		else if (keyword == "FUNC")
			statement = Function::make(verbatim.toString(), ScopeType::Root);	//TODO how can we figure out the outter block?
		else if (keyword == "PREP")
			statement = Preprocessor::make(verbatim.toString());
		else if (keyword == "VAR")
			statement = Variable::make(verbatim.toString());
		else
		{
			qDebug() << "ParseScript: Unknown keyword " << keyword;
			return;
		}

		int currentTier = indentation+1;

		//save the current statement in the correct tier
		{
			if (mPreviousStatementTiers.count() == currentTier)
				mPreviousStatementTiers.push_back(statement);
			else if (mPreviousStatementTiers.count() < currentTier)
			{
				qDebug() << "ParseScript: Too much indentation";
				return;
			}
			else
				mPreviousStatementTiers[currentTier] = statement;
		}

		//add the current statement to the super tier
		{
			Statement *superTier = mPreviousStatementTiers[currentTier-1];

			if (auto block = dynamic_cast<Block*>(superTier))
				block->appendStatement(statement);
			else if (auto subBlock = dynamic_cast<SubBlock*>(superTier))
				subBlock->block().appendStatement(statement);
			else if (auto cls = dynamic_cast<Class*>(superTier))
			{
				//TODO fill in later
			}
		}
	}
};