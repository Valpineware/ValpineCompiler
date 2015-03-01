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
			QString mClassName;
			QVector<QString> mPublicDecs;
			QVector<QString> mPrivateDecs;
			QVector<QString> mProtectedDecs;

			int mScope;

			void buildClass(QVector<QString> &body, const graph::Class &classDef);
			void buildMember(QVector<QString> &body, const graph::Class::Member &member, QVector<QString> &decs);
		public:
			Class(QVector<QString> &body, QVector<QString> &includes, const graph::Class &classDef, int scope);
			
			//QVector<QString> createHeaderFile();
		};



	}
}



#endif