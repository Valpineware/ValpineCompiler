//==================================================================================================================|
// Created 2015.01.29 by Daniel L. Watkins
//
// Copyright (C) 2015 Valpineware
// This file is licensed under the MIT License.
//==================================================================================================================|

#include <Library.h>

#include "SubBlock.h"
#include "TypeExpression.h"

#ifndef _vc_graph_Function_h
#define _vc_graph_Function_h

namespace vc { namespace graph
{
	struct Parameter
	{
		TypeExpression type;
		QString id;
		QString defaultValue;
	};


	/**
	 * @brief Represents the body of a function of control structure that is executed.
	 */
	class Function : public SubBlock
	{
	public:
		Function() = delete;
		Function(const QString &verbatim) : SubBlock(verbatim) {}

		static Function* createFromVerbatimSignature(const QString &signature, ScopeType scopeType);

		enum class Type
		{
			Normal,
			Constructor,
			Destructor
		};

		void setType(Type type) { mType = type; }
		Type type() const { return mType; }

		void setReturnType(const TypeExpression &returnType) { mReturnType = returnType; }
		TypeExpression returnType() const { return mReturnType; }
		void setId(const QString &id) { mId = id; }
		QString id() const { return mId; }
		
		void addParameter(const Parameter &parameter) { mParameters.append(parameter); }
		const QVector<Parameter>& parameters() const { return mParameters; }

	private:
		QString mId;
		Type mType = Type::Normal;
		TypeExpression mReturnType;
		QVector<Parameter> mParameters;
	};
}}

#endif
