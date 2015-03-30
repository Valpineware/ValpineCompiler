//==================================================================================================================|
// Created 2015.02.19 by John Koehn
//
// Copyright (C) 2015 Valpineware
// This file is licensed under the MIT License.
//==================================================================================================================|

#ifndef _vc_mocker_ControlStructure_h
#define _vc_mocker_ControlStructure_h

#include <Graph/Graph.h>
#include <Library.h>
#include "Function.h"

namespace vc {	namespace mocker {

	/**
	* Class creates control structures and reads there body contents
	*/
	class ControlStructure
	{
	private:
		void buildStatement(graph::ControlStructure &controlStructure, MockerData &data, QQueue<const graph::Function*> &functions);

	public:
		ControlStructure(graph::ControlStructure &controlStructure, MockerData &data, QQueue<const graph::Function*> &functions);
	};





}}



#endif