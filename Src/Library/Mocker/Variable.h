//==================================================================================================================|
// Created 2015.02.08 by John Koehn
//
// Copyright (C) 2015 Valpineware
// This file is licensed under the MIT License.
//==================================================================================================================|

#ifndef _vc_mocker_Variable_h
#define _vc_mocker_Variable_h

#include <Graph/Graph.h>
#include <Library.h>
#include "Mocker.h"

namespace vc { namespace mocker 
{
	/**
	* Deals with variable conversions to c++
	*/
	class Variable
	{
	private:
		static const QString createVarInternal(MockerData &data, graph::Variable &var);

	public:
		static void createVarClass(MockerData &data, graph::Variable &var, QString &classID, const ScopeState state);
		static void createVar(MockerData &data, graph::Variable &var);
	};



}}


#endif