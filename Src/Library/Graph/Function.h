//==================================================================================================================|
// Created 2015.01.29 by Daniel L. Watkins
//
// Copyright (C) 2015 Valpineware
// This file is licensed under the MIT License.
//==================================================================================================================|

#include <Library.h>

#include "Statement.h"
#include "Block.h"

#ifndef _vc_graph_Function_h
#define _vc_graph_Function_h

namespace vc { namespace graph
{
	struct Parameter
	{
		QString type;
		QString id;
		QString defaultValue;
	};


	/**
	 * @brief Represents the body of a function of control structure that is executed.
	 */
	class Function : public Statement
	{
	public:
		Function() = delete;
		Function(const QString &verbatim) : Statement(verbatim) {}

		void setId(const QString &id) { mId = id; }
		QString id() const { return mId; }
		void setReturnType(const QString &returnType) { mReturnType = returnType; }
		QString returnType() const { return mReturnType; }

		void addParameter(const Parameter &parameter) { mParameters.append(parameter); }
		const QVector<Parameter>& parameters() const { return mParameters; }


		Block& block() { return mBlock; }	//TODO move this into a base class so Function and Control can share this
		const Block& block() const { return mBlock; }

	private:
		Block mBlock;
		QString mId;
		QString mReturnType;
		QVector<Parameter> mParameters;
	};
}}

#endif
