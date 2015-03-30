//==================================================================================================================|
// Created 2015.02.22 by John Koehn
//
// Copyright (C) 2015 Valpineware
// This file is licensed under the MIT License.
//==================================================================================================================|

#ifndef _vc_mocker_Class_h
#define _vc_mocker_Class_h

#include <Graph/Graph.h>
#include <Library.h>

#include "Mocker.h"

namespace vc { namespace mocker
{
	/**
	* Converts a Class to cpp
	*/
	class Class
	{
	private:
		QString mClassName;
		int mScope;

		void buildClass(MockerData &data, const graph::Class &classDef);
		void buildMember(MockerData &data, const graph::Class::Member &member, const ScopeState state);
		void buildHeader(MockerData &data);
	public:
		Class(MockerData &data, const graph::Class &classDef);
			
	};



}}



#endif