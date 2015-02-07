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
	void Compiler::compile(const QString &mockFilepath, const QString &outputFilepath)
	{
		QString program = "g++";
		QStringList arguments;

		QFileInfo fileInfo(mockFilepath);
		arguments << mockFilepath << "-o" << outputFilepath;

		QObject::connect(&mProcess, SIGNAL(error(QProcess::ProcessError)),
						 this, SLOT(onCompileProcessError(QProcess::ProcessError)));

		QObject::connect(&mProcess, SIGNAL(finished(int, QProcess::ExitStatus)),
						 this, SLOT(onCompileProcessFinished(int, QProcess::ExitStatus)));

		mProcess.start(program, arguments);
		mProcess.waitForFinished(mTimeoutMs);
	}


	void Compiler::onCompileProcessError(QProcess::ProcessError error)
	{
		switch (error)
		{
		case QProcess::FailedToStart:
			qDebug() << "G++: The process failed to start. Either the invoked program is missing, or you may have insufficient permissions to invoke the program."; break;
		case QProcess::Crashed:
			qDebug() << "G++: crashed!"; break;
		case QProcess::Timedout:
			qDebug() << "G++: Compile timed out after " << mTimeoutMs/1000 << " seconds and has been terminated."; break;
		case QProcess::ReadError:
			qDebug() << "G++: An error occurred when attempting to read from the process. For example, the process may not be running."; break;
		case QProcess::WriteError:
			qDebug() << "G++: An error occurred when attempting to write to the process. For example, the process may not be running, or it may have closed its input channel."; break;
		case QProcess::UnknownError:
			qDebug() << "G++: An unknown error occured while running."; break;
		}
	}


	void Compiler::onCompileProcessFinished(int exitCode, QProcess::ExitStatus exitStatus)
	{
		qDebug() << "C++ compiler finished with exit code " << exitCode << " and status " << static_cast<int>(exitStatus);
	}
}}