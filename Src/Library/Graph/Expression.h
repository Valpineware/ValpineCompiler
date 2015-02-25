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
	/**
	 * @brief
	 */
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

		private:
			QString mVerbatim;
		};

		typedef QList<Component*> ComponentList;
		typedef QListIterator<Component*> ComponentListIterator;


		/**
		 * The contains a list of all components in a sub-expression.
		 */
		class Result : public Component
		{
		public:
			Result(const QString &verbatim);
			~Result();
			
			ComponentList& components() { return mComponents; }
			const ComponentList& components() const { return mComponents; }

		private:
			QList<Component*> mComponents;
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
			Operator(const QString &verbatim) : Component(verbatim) {}
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
			Id(const QString &verbatim) : Component(verbatim) {}

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
		class Arguments : public Component
		{
		public:

			Arguments(const QString &verbatim);
			const ComponentList& list() const { return mList; }
			ComponentList& list() { return mList; }

		private:
			ComponentList mList;
		};

	public:
		Expression() = delete;

		/**
		 * Parses \p verbatim and builds an in-memory representation of the expression.
		 */
		Expression(const QString &verbatim);

		ComponentList& components() { return mRoot.components(); }
		const ComponentList& components() const { return mRoot.components(); }

	private:
		Result mRoot;
	};
}}

#endif
