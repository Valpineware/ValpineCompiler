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
	public:
		static void createVar(MockerData &data, graph::Variable &var);
	};



}}


#endif