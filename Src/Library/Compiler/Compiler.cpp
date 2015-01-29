//==================================================================================================================|
// Created 2015.01.28 by Daniel L. Watkins
//
// Copyright (C) 2015 Valpineware
// This file is licensed under the MIT License.
//==================================================================================================================|

#include <Library.h>
#include "Compiler.h"

namespace vc { namespace compiler
{
	void Compiler::compile(const QString &filepath)
	{
		QString program = "g++";
		QStringList arguments;
		arguments << "Main.cpp" << "-o" << "Main.exe";

		QObject::connect(&mProcess, SIGNAL(error(QProcess::ProcessError)),
						 this, SLOT(onCompileProcessError(QProcess::ProcessError)));

		QObject::connect(&mProcess, SIGNAL(finished(int, QProcess::ExitStatus)),
						 this, SLOT(onCompileProcessFinished(int, QProcess::ExitStatus)));

		mProcess.start(program, arguments);
		mProcess.waitForFinished(mTimeoutMs);

		if (mProcess.error() == QProcess::ProcessError::Timedout)
		{
			qDebug() << "Compile timed out after " << mTimeoutMs/1000 << " seconds.";
		}
	}



	void Compiler::onCompileProcessError(QProcess::ProcessError error)
	{
		qDebug() << "C++ compiler process encountered an error code=" << static_cast<int>(error);
	}


	void Compiler::onCompileProcessFinished(int exitCode, QProcess::ExitStatus exitStatus)
	{
		qDebug() << "C++ compiler finished with exit code " << exitCode << " and status " << static_cast<int>(exitStatus);
	}
}}