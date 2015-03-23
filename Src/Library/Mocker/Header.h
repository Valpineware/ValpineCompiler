//==================================================================================================================|
// Created 2015.03.17 by John Koehn
//
// Copyright (C) 2015 Valpineware
// This file is licensed under the MIT License.
//==================================================================================================================|

#ifndef _vc_mocker_Class_h
#define _vc_mocker_Class_h

#include <Graph/Graph.h>
#include <Library.h>
#include "ClassHeader.h"

namespace vc { namespace mocker
{
	enum ScopeState
	{
		scopePrivate,
		scopePublic,
		scopeProtected,		
	};
	
	/**
	* Contains data for a cpp header file
	*/
	class Header
	{
	private:
		QVector<QString> mFunctionDecs;
		QVector<ClassHeader> mClassHeaders;

		int mScopeLevel;
	public:
		Header(int scopeLevel);
			
		void addClass(QString &className);
		void addFunctionDec(QString &functionDec);
		void addClassMember(QString &classID, QString &memberDec, ScopeState state);

		QVector<QString> buildHeader();
			
	};
}}



#endif