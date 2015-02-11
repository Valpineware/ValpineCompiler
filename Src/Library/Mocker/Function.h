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
		QString mDeclartion;;
		void buildDeclartion(QVector<QString> &body, graph::Function &function);
		void buildBody(QVector<QString> &body, graph::Block &block);

	public:
		Function(QVector<QString> &body, graph::Function &function) { buildDeclartion(body, function); buildBody(body, function.block()); };
		QString& declartion() { return mDeclartion; }
	};



}}




#endif