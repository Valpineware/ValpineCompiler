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

namespace vc {	namespace mocker {

	/**
	* Class creates control structures and reads there body contents
	*/
	class ControlStructure
	{
	private:
		QVector<QString> *mBody;
		graph::ControlStructure *mControlStructure;

		void buildStatement();
		void buildBody();

	public:
		ControlStructure(QVector<QString> &body, graph::ControlStructure &controlStatement);
	};





}}



#endif