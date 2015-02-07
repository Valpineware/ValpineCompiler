//==================================================================================================================|
// Created 2015.01.28 by Daniel L. Watkins
//
// Copyright (C) 2015 Valpineware
// This file is licensed under the MIT License.
//==================================================================================================================|

#ifndef _vc_compiler_Compiler_h
#define _vc_compiler_Compiler_h

#include <Library.h>

namespace vc { namespace compiler
{
	class Compiler : public QObject
	{
		Q_OBJECT

	public:
		void compile(const QString &mockFilepath, const QString &outputFilepath);


	private slots:
		void onCompileProcessError(QProcess::ProcessError error);
		void onCompileProcessFinished(int exitCode, QProcess::ExitStatus exitStatus);


	private:
		QProcess mProcess;
		const int mTimeoutMs = 1000 * 60 * 10;	//10 minutes
	};
}}

#endif
