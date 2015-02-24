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


		class Id : public Component
		{
		public:
			Id(const QString &verbatim) : Component(verbatim), mType(Type::Function) {}

			enum class Type
			{
				Basic,	//TODO not sure if this naming is good enough
				Function
			};

			Type type() const { return mType; }

		private:
			Type mType;
		};


		class Arguments : public Component
		{
		public:
			Arguments(const QString &verbatim);

			const QList<Component*>& list() const { return mList; }

		private:
			QList<Component*> mList;
		};


	public:
		Expression() = delete;
		Expression(const QString &verbatim);

		const ComponentList& components() const { return mRoot.components(); }

	private:
		Result mRoot;
	};
}}

#endif
