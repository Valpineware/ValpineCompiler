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
		 * The result of a sub-expression (a+10), identifier (foo), or constant (42.0). 
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


		class Operator : public Component
		{
		public:
			Operator(const QString &verbatim) : Component(verbatim) {}
		};


		class Value : public Component
		{
		public:
			Value(const QString &verbatim) : Component(verbatim) {}
		};


	public:
		Expression() = delete;
		Expression(const QString &verbatim);

		const Result& result() const { return mRoot; }

	private:
		Result mRoot;
	};
}}

#endif
