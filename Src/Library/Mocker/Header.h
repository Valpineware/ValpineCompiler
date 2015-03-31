//==================================================================================================================|
// Created 2015.03.17 by John Koehn
//
// Copyright (C) 2015 Valpineware
// This file is licensed under the MIT License.
//==================================================================================================================|

#ifndef _vc_mocker_Header_h
#define _vc_mocker_Header_h

#include <Graph/Graph.h>
#include <Library.h>
#include "ClassHeader.h"a

namespace vc { namespace mocker
{
	enum ScopeState
	{
		scopePrivate,
		scopePublic,
		scopeProtected,	
		none,
	};
	
	/**
	* Contains data for a cpp header file
	*/
	class Header
	{
	private:
		QVector<QString> mFunctionDecs;
		QVector<QString> mIncludes;
		QVector<ClassHeader *> mClassHeaders;

		int mScopeLevel;
	public:
		Header(int scopeLevel = 0);
		
		void addInclude(QString &include);
		void addClass(QString &className);
		void addFunctionDec(QString &functionDec);
		void addClassMember(const QString &classID, QString &memberDec, const ScopeState state);

		void buildHeader(QTextStream &outStream);

		int getScopeLevel() { return mScopeLevel; }
			
	};
}}



#endif