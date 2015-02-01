//==================================================================================================================|
// Created 2015.01.31 by Daniel L. Watkins
//
// Copyright (C) 2015 Valpineware
// This file is licensed under the MIT License.
//==================================================================================================================|

#ifndef _vc_parser_Recognizer_h
#define _vc_parser_Recognizer_h

#include <Library.h>
#include <Graph/Function.h>

namespace vc { namespace parser
{
	/**
	 * @brief Determines what given Valpine code fragments are
	 */
	class Recognizer
	{
	public:
		static graph::Function* parseFunctionSignature(const QString &signature);
	};
}}

#endif
