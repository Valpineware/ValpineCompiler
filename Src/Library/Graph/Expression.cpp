//==================================================================================================================|
// Created 2015.02.20 by Daniel L. Watkins
//
// Copyright (C) 2015 Valpineware
// This file is licensed under the MIT License.
//==================================================================================================================|

#include "Expression.h"

namespace vc { namespace graph
{
	Expression::~Expression()
	{
		for (Component *cmp : mComponents)
			delete cmp;
	}


	Expression* Expression::createFromVerbatimSignature(const QString signature)
	{
		Expression *expression = new Expression(signature);

		expression->mComponents.append(new Identifier(signature));

		return expression;
	}
}}