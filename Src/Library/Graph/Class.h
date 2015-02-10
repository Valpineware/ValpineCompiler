//==================================================================================================================|
// Created 2015.02.05 by Daniel L. Watkins
//
// Copyright (C) 2015 Valpineware
// This file is licensed under the MIT License.
//==================================================================================================================|

#ifndef _vc_graph_Class_h
#define _vc_graph_Class_h

#include "Statement.h"
#include "Function.h"

namespace vc { namespace graph
{
	/**
	 * @brief
	 */
	class Class : public Statement
	{
	public:
		/**
		 * Access type for members
		 */
		enum AccessType
		{
			Private,
			Protected,
			Public
		};


		/**
		 * @brief Associates an AccessType with a Statement
		 */
		struct Member
		{
			Member() {}

			AccessType accessType = AccessType::Private;
			Statement *statement = nullptr;

			~Member()
			{
				if (statement != nullptr)
					delete statement;
			}

		private:
			Q_DISABLE_COPY(Member);	//effectively forces heap allocation since our destructor deletes statement
		};


		/**
		 * @brief Associates an AccessType with a string. Used for listing super classes and interfaces.
		 */
		struct AccessIdPair
		{
			AccessType accessType = Private;
			QString id;
		};


	public:
		Class(const QString &verbatim) : Statement(verbatim) {}

		/**
		 * @returns nullptr if \p signature does not represent a valid class header. Otherwise
		 * a new Class instance is returned with the id value set according to \p signature.
		 */
		static Class* createFromVerbatimSignature(const QString &signature);	//TODO extract this into a common template interface

		QString id() const { return mId; }
		const QList<Member*>& members() const { return mMembers; }
		void addMember(Member *member) { mMembers.append(member); }

		/*
		 * @returns the super classes this class inherits.
		 */
		const QList<AccessIdPair>& superClasses() { return mSuperClasses; }

		/*
		 * @returns the interfaces this class implements.
		 */
		const QList<AccessIdPair>& interfaces() { return mInterfaces; }

	private:
		QString mId;
		QList<Member*> mMembers;
		QList<AccessIdPair> mSuperClasses, mInterfaces;
	};
}}

#endif
