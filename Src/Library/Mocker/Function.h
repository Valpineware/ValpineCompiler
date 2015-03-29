//==================================================================================================================|
// Created 2015.02.08 by John Koehn
//
// Copyright (C) 2015 Valpineware
// This file is licensed under the MIT License.
//==================================================================================================================|

#ifndef _vc_mocker_Function_h
#define _vc_mocker_Function_h

#include <Graph/Graph.h>
#include <Library.h>
#include "Mocker.h"

namespace vc { namespace mocker 
{
	/**
	* @breif Contains information on cpp function conversion
	*/
	class Function
	{
	private:
		void buildDeclartion(MockerData &data, const graph::Function &function, const QString &classID, const ScopeState state);

	public:
		Function(MockerData &data, const graph::Function &function, const QString &classID, QQueue<const graph::Function*> &functions, const ScopeState state);
	};



}}




#endif