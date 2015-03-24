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
		const QString * mClassID;
		QVector<const QString> mPrivateMembers;
		QVector<const QString> mPublicMembers;
		QVector<const QString> mProtectedMembers;

		int mScopeLevel;

	public:
		ClassHeader(const QString &classID, int scopeLevel);

		void addPrivateMember(const QString &member)		{ mPrivateMembers.append(Utility::createTabs(mScopeLevel + 1) + member); }
		void addPublicMember(const QString &member)		{ mPublicMembers.append(Utility::createTabs(mScopeLevel + 1) + member); }
		void addProtectedMember(const QString &member)	{ mProtectedMembers.append(Utility::createTabs(mScopeLevel + 1) + member); }

		QVector<const QString> buildClass();
		const QString getClassID()						{ return *mClassID; }
		
	};
}}

#endif