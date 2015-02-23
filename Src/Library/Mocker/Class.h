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

namespace vc {
	namespace mocker
	{
		/**
		* Converts a Class to cpp
		*/
		class Class
		{
		private:

		public:
			Class(QVector<QString> &body, QVector<QString> &forwardDecs, const graph::Class &classDef, int scope);
			
		};



	}
}



#endif