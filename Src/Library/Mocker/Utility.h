//==================================================================================================================|
// Created 2015.02.20 by John Koehn
//
// Copyright (C) 2015 Valpineware
// This file is licensed under the MIT License.
//==================================================================================================================|

#ifndef _vc_mocker_Utility_h
#define _vc_mocker_Utility_h

#include <Graph/Graph.h>
#include <Library.h>

namespace vc { namespace mocker
{
		class Utility
		{
		public:
			static QString createTabs(int scopeLevel);
			static void vectorToStream(QTextStream &outStream, QVector<QString> &vecData);
		};

}}

#endif