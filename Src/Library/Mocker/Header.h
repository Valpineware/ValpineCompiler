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
#include "ClassHeader.h"

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
		QVector<const QString> mFunctionDecs;
		QVector<const QString> includes;
		QVector<ClassHeader> mClassHeaders;

		int mScopeLevel;
	public:
		Header(int scopeLevel = 0);
		
		void addInclude(const QString &include);
		void addClass(const QString &className);
		void addFunctionDec(const QString &functionDec);
		void addClassMember(const QString &classID, const QString &memberDec, const ScopeState state);

		QVector<const QString> buildHeader();
			
	};
}}



#endif