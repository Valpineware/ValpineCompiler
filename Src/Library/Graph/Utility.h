//==================================================================================================================|
// Created 2015.02.08 by Daniel L. Watkins
//
// Copyright (C) 2015 Valpineware
// This file is licensed under the MIT License.
//==================================================================================================================|

#ifndef _vc_graph_Utility_h
#define _vc_graph_Utility_h

#include <Library.h>

namespace vc { namespace graph
{
	class TypeExpression;

	/**
	 * @brief 
	 */
	class Utility
	{
	public:
		static void breakUpByWhitespace(const QString &what, QStringList &list);

		static bool parseTypeExpression(QStringListIterator &i, TypeExpression &typeExpression);
	};
}}

#endif
