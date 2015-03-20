//==================================================================================================================|
// Created 2015.03.18 by John Koehn
//
// Copyright (C) 2015 Valpineware
// This file is licensed under the MIT License.
//==================================================================================================================|

#ifndef _vc_mocker_ClassHeader_h
#define _vc_mocker_ClassHeader_h

#include <Graph/Graph.h>
#include <Library.h>
#include "Utility.h"

namespace vc { namespace mocker
{
	class ClassHeader
	{
	private:
		QString mClassID;
		QVector<QString> mPrivateMembers;
		QVector<QString> mPublicMembers;
		QVector<QString> mProtectedMembers;

		int mScopeLevel;

	public:
		ClassHeader(QString &classID, int scopeLevel);

		void addPrivateMember(QString &member)		{ mPrivateMembers.append(Utility::createTabs(mScopeLevel + 1) + member); }
		void addPublicMember(QString &member)		{ mPublicMembers.append(Utility::createTabs(mScopeLevel + 1) + member); }
		void addProtectedMember(QString &member)	{ mProtectedMembers.append(Utility::createTabs(mScopeLevel + 1) + member); }

		QVector<QString> buildClass();
		QString getClassID()						{ return mClassID; }
		
	};
}}

#endif