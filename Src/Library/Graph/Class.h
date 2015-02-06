//==================================================================================================================|
// Created 2015.02.05 by Daniel L. Watkins
//
// Copyright (C) 2015 Valpineware
// This file is licensed under the MIT License.
//==================================================================================================================|

#ifndef _vc_graph_Class_h
#define _vc_graph_Class_h

#include "SubBlock.h"
#include "Function.h"

namespace vc { namespace graph
{
	/**
	 * @brief Represents a "class" construct.
	 */
	class Class : public SubBlock
	{
	public:
		Class(const QString &verbatim) : SubBlock(verbatim) {}

		/**
		 * @returns nullptr if \p signature does not represent a valid class header. Otherwise
		 * a new Class instance is returned with the id value set according to \p signature.
		 */
		static Class* createFromVerbatimSignature(const QString &signature);

		QString id() const { return mId; }

		/**
		 * Baseclass used to distinguish the access type of statements within a Class.
		 * Subclasses should inherit from Member and from a designated Statement type.
		 */
		class Member
		{
		public:
			enum AccessType
			{
				Private,
				Protected,
				Public
			};

			AccessType accessType() { return Public; }
		};


		/**
		 * @brief Represents a Member Function
		 */
		class Method : public Member, public Function
		{
			Method(const QString &verbatim) : Function(verbatim) {}
		};


		/**
		 * @brief Represents an instance variable. TODO for now any statement is valid YIKES
		 */
		class IVar : public Member, public Statement
		{
			IVar(const QString &verbatim) : Statement(verbatim) {}
		};

	private:
		QString mId;
	};
}}

#endif
