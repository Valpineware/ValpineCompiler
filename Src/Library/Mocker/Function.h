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

namespace vc { namespace mocker 
{
	/**
	* @breif Contains information on cpp function conversion
	*/
	class Function
	{
	private:
		QString mDeclartion;
		QQueue<graph::Function*> mNestedFunctions;
		void buildDeclartion(QVector<QString> &body, QVector<QString> &forwardDecs, graph::Function &function);
		void buildBody(QVector<QString> &body, graph::Function &function);


	public:
		Function(QVector<QString> &body, QVector<QString> &forwardDecs, graph::Function &function);
		QQueue<graph::Function*>& nestedFunctions() { return mNestedFunctions; }
	};



}}




#endif