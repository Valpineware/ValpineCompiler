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
		Expression(const QString &verbatim) : Statement(verbatim) {}
		~Expression();

		static Expression* createFromVerbatimSignature(const QString signature);

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


		class Identifier : public Component
		{
		public:
			Identifier(const QString &verbatim) : Component(verbatim) {}
		};

		
		typedef QList<Component*> ComponentList;
		typedef QListIterator<Component*> ComponentListIterator;
		const ComponentList& components() const { return mComponents; }

	private:
		QList<Component*> mComponents;
	};
}}

#endif
