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
	struct FileData
	{
		QVector<QString> *body;
		QVector<QString> *forwardDecs;
		int scope;
		QQueue<const graph::Function*> *functions;
	};

	class DeclarationBlock
	{
	private:
		FileData mData;

		void createFunction();
	public:
		DeclarationBlock(QVector<QString> &body, QVector<QString> &forwardDecs, const graph::Function &function, int scope);
		void static buildBlock(const graph::Block &block, FileData &data);
	};

}}

#endif