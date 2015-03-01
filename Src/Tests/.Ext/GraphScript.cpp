//==================================================================================================================|
// Created 2015.02.28 by Daniel L. Watkins
//
// Copyright (C) 2015 Valpineware
// This file is licensed under the MIT License.
//==================================================================================================================|

#include "GraphScript.h"

namespace ext
{
	bool GraphScript::parse(const QString &filepath)
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


	bool GraphScript::parseLine(const QString &line, int lineNumber)
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
			//special keyword
			applyStatement(indentation, line.rightRef(line.count()-lastLeadingTab), QStringRef(nullptr));
		}
		else
		{
			QStringRef keyword = line.midRef(lastLeadingTab, space-lastLeadingTab);
			QStringRef verbatim = line.rightRef(line.count()-space-1);
			applyStatement(indentation, keyword, verbatim);
		}

		return true;
	}


	void GraphScript::applyStatement(int indentation, const QStringRef &keyword, const QStringRef &verbatim)
	{
		//check for special keywords
		if (verbatim.isNull())
		{
			if (keyword == "ENABLE_PUBLIC")
				mCurrentAccessType = Class::Public;
			else if (keyword == "ENABLE_PROTECTED")
				mCurrentAccessType = Class::Protected;
			else if (keyword == "ENABLE_PRIVATE")
				mCurrentAccessType = Class::Private;

			return;
		}
			
		Statement *statement = nullptr;
		int currentTier = indentation+1;
		Statement *superTier = mPreviousStatementTiers[currentTier-1];

		if (keyword == "STATE")
			statement = new Statement(verbatim.toString());
		else if (keyword == "CLASS")
		{
			statement = Class::make(verbatim.toString());
			mCurrentAccessType = Class::Private;
		}
		else if (keyword == "CONTROL")
			statement = ControlStructure::make(verbatim.toString());
		else if (keyword == "FUNC")
		{
			ScopeType currentScope = ScopeType::Root;
			if (dynamic_cast<Class*>(superTier))
				currentScope = ScopeType::ClassBlock;
			else if (currentTier > 0)
				currentScope = ScopeType::ExecutionBlock;

			statement = Function::make(verbatim.toString(), currentScope);	//TODO how can we figure out the outter block?
		}
		else if (keyword == "PREP")
			statement = Preprocessor::make(verbatim.toString());
		else if (keyword == "VAR")
			statement = Variable::make(verbatim.toString());
		else
		{
			qDebug() << "GraphScript: Unknown keyword " << keyword;
			return;
		}

		//save the current statement in the correct tier
		{
			if (mPreviousStatementTiers.count() == currentTier)
				mPreviousStatementTiers.push_back(statement);
			else if (mPreviousStatementTiers.count() < currentTier)
			{
				qDebug() << "GraphScript: Too much indentation";
				return;
			}
			else
				mPreviousStatementTiers[currentTier] = statement;
		}

		//add the current statement to the super tier
		{
			if (auto block = dynamic_cast<Block*>(superTier))
				block->appendStatement(statement);
			else if (auto subBlock = dynamic_cast<SubBlock*>(superTier))
				subBlock->block().appendStatement(statement);
			else if (auto cls = dynamic_cast<Class*>(superTier))
			{
				Class::Member *member = new Class::Member;
				member->accessType = mCurrentAccessType;
				member->statement = statement;
				cls->addMember(member);
			}
		}
	}
};