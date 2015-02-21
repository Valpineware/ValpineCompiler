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
	struct Data
	{
		QVector<QString> *body;
		QVector<QString> *forwardDecs;
		int scope; 
		QQueue<graph::Function*> *nestedFunctions;
	};

	/**
	* @breif Contains information on cpp function conversion
	*/
	class Function
	{
	private:
		Data mData;
		void buildDeclartion(const graph::Function &function);


	public:
		Function(QVector<QString> &body, QVector<QString> &forwardDecs, const graph::Function &function, int scope);
		QQueue<graph::Function*> &nestedFunctions() { return *(mData.nestedFunctions); }
		Data &data() { return mData; }
	};



}}




#endif