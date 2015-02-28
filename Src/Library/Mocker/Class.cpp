//==================================================================================================================|
// Created 2015.02.22 by John Koehn
//
// Copyright (C) 2015 Valpineware
// This file is licensed under the MIT License.
//==================================================================================================================|

#include "Class.h"
#include "Variable.h"
#include "DeclarationBlock.h"
#include "Utility.h"

namespace vc { namespace mocker
{
	Class::Class(QVector<QString> &body, const graph::Class &classDef, int scope)
	{
		mScope = scope;

		buildClass(body, classDef);
	}

	void Class::buildClass(QVector<QString> &body, const graph::Class &classDef)
	{
		mClassName = classDef.id();

		//loop through member and build the graph
		auto iter = vc::makeIter(classDef.members());
		while (iter.hasNext())
		{
			const graph::Class::Member *member = iter.next();

			switch (member->accessType)
			{
			case graph::Class::Private:
				buildMember(body, *member, mPrivateDecs);
				break;
			case graph::Class::Public:
				buildMember(body, *member, mPublicDecs);
				break;
			case graph::Class::Protected:
				buildMember(body, *member, mProtectedDecs);
			}
		}
	}

	void Class::buildMember(QVector<QString> &body, const graph::Class::Member &member, QVector<QString> &decs)
	{
		graph::Statement *statement = member.statement;
		if (auto * variable = dynamic_cast<graph::Variable*>(statement))
		{
			Variable::createVar(decs, *variable, mScope);
		}
		else if (auto * function = dynamic_cast<graph::Function*>(statement))
		{
			DeclarationBlock block(body, decs, *function, mScope);
		}
		else
		{
			body.append(Utility::createTabs(mScope));
		}
	}

}}