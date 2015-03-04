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
#include "Mocker.h"

namespace vc { namespace mocker
{
	class DeclarationBlock
	{
	private:
		QQueue<const graph::Function*> mFunctions;

		void createFunction(MockerData &data, const QString &classID);
	public:
		DeclarationBlock(MockerData &data, const graph::Function &function, const QString classID = "");

		//TODO, was a total bipshit. refactor to private
		void static buildBlock(const graph::Block &block, MockerData &data, QQueue<const graph::Function*> &functions);
	};

}}

#endif