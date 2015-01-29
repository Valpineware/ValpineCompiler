//==================================================================================================================|
// Created 2015.01.28 by Daniel L. Watkins
//
// Copyright (C) 2015 Valpineware
// This file is licensed under the MIT License.
//==================================================================================================================|

#include <QtCore/QProcess>

class CppCompiler : public QObject
{
	Q_OBJECT

public:
	void run();


private slots:
	void onCompileProcessError(QProcess::ProcessError error);
	void onCompileProcessFinished(int exitCode, QProcess::ExitStatus exitStatus);


private:
	QProcess mCompilerProcess;
	const int mCompileTimeoutMs = 1000 * 60 * 10;	//10 minutes
};