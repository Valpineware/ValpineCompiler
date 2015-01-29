//==================================================================================================================|
// Created 2015.01.28 by Daniel L. Watkins
//
// Copyright (C) 2015 Valpineware
// This file is licensed under the MIT License.
//==================================================================================================================|

#include <CppCompiler.h>
#include <Library.h>

void CppCompiler::run()
{
	QString program = "g++";
	QStringList arguments;
	arguments << "Main.cpp" << "-o" << "Main.exe";

	QObject::connect(&mCompilerProcess, SIGNAL(error(QProcess::ProcessError)),
					 this, SLOT(onCompileProcessError(QProcess::ProcessError)));

	QObject::connect(&mCompilerProcess, SIGNAL(finished(int, QProcess::ExitStatus)),
					 this, SLOT(onCompileProcessFinished(int, QProcess::ExitStatus)));

	mCompilerProcess.start(program, arguments);
	mCompilerProcess.waitForFinished(mCompileTimeoutMs);

	if (mCompilerProcess.error() == QProcess::ProcessError::Timedout)
	{
		qDebug() << "Compile timed out after " << mCompileTimeoutMs/1000 << " seconds.";
	}
}



void CppCompiler::onCompileProcessError(QProcess::ProcessError error)
{
	qDebug() << "C++ compiler process encountered an error code=" << static_cast<int>(error);
}


void CppCompiler::onCompileProcessFinished(int exitCode, QProcess::ExitStatus exitStatus)
{
	qDebug() << "C++ compiler finished with exit code " << exitCode << " and status " << static_cast<int>(exitStatus);
}