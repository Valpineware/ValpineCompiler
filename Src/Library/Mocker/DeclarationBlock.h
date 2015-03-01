//==================================================================================================================|
// Created 2015.02.20 by John Koehn
//
// Copyright (C) 2015 Valpineware
// This file is licensed under the MIT License.
//==================================================================================================================|

#ifndef _vc_mocker_DeclarationBlock_h
#define _vc_mocker_DeclarationBlock_h

#include <Graph/Graph.h>
#include <Library.h>

namespace vc { namespace mocker
{
	struct FunctionData
	{
		QVector<QString> *body;
		QVector<QString> *forwardDecs;
		int scope;
		QQueue<const graph::Function*> *functions;
		const QString *classID;
	};

	class DeclarationBlock
	{
	private:
		FunctionData mData;

		void createFunction();
	public:
		DeclarationBlock(QVector<QString> &body, QVector<QString> &forwardDecs, const graph::Function &function, int scope, const QString classID = "");
		void static buildBlock(const graph::Block &block, FunctionData &data);
	};

}}

#endif