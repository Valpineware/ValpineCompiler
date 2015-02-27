//==================================================================================================================|
// Created 2015.02.20 by Daniel L. Watkins
//
// Copyright (C) 2015 Valpineware
// This file is licensed under the MIT License.
//==================================================================================================================|

#ifndef _vc_graph_Expression_h
#define _vc_graph_Expression_h

#include "Statement.h"

namespace vc { namespace graph
{
	class Expression : public Statement
	{
	public:
		/**
		* Base type for the various types of components in an expression.
		*/
		class Component
		{
		public:
			Component() = delete;
			Component(const QString &verbatim) : mVerbatim(verbatim) {}
			virtual ~Component() {}

			QString verbatim() const { return mVerbatim; }

		protected:
			void setVerbatim(const QString &verbatim) { mVerbatim = verbatim; }

		private:
			QString mVerbatim;
		};


		typedef QList<Component*> ComponentList;
		typedef QListIterator<Component*> ComponentListIterator;


		class ComponentListUser
		{
		public:
			ComponentList& components() { return mComponents; }
			const ComponentList& components() const { return mComponents; }

			ComponentListUser() {}

			~ComponentListUser()
			{
				for (Component *cmp : mComponents)
					delete cmp;
			}

		private:
			Q_DISABLE_COPY(ComponentListUser)
			ComponentList mComponents;
		};


		/**
		* The contains a list of all components in a sub-expression.
		*/
		class InnerExpression : public Component, public ComponentListUser
		{
		public:
			InnerExpression() : Component("") {}

			static InnerExpression* make(const QString &verbatim);
		};


		/**
		* An operator
		*/
		class Operator : public Component
		{
		public:
			/**
			* Simply sets the verbatim to \p verbatim.
			*/
			Operator() : Component("") {}

			static Operator* make(const QString &verbatim);
		};


		/**
		* An identifier that refers to a variable, numeric constant, or function call.
		*/
		class Id : public Component
		{
		public:
			/**
			* Simply sets the verbatim to \p verbatim.
			*/
			Id() : Component("") {}

			static Id* make(const QString &verbatim);

			/**
			* The type of identifier.
			*/
			enum class Type
			{
				Basic,			/*! A variable or numeric constant */
				FunctionCall	/*! A call to a function*/
			};

			void setType(Type type) { mType = type; }
			Type type() const { return mType; }

		private:
			Type mType = Type::Basic;
		};


		/**
		* Holds a list components each representing an argument to a particular function call.
		*/
		class Arguments : public Component, public ComponentListUser
		{
		public:
			Arguments() : Component("") {}

			static Arguments* make(const QString &verbatim);
		};

	public:
		Expression() : Expression("") {}
		Expression(const QString verbatim) : Statement(verbatim), mInnerExpression(InnerExpression::make(verbatim)) {}

		ComponentList& components() { return mInnerExpression->components(); }
		const ComponentList& components() const { return mInnerExpression->components(); }

	private:
		unique<InnerExpression> mInnerExpression;
	};
}}

#endif
