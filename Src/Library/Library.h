#ifndef LIBRARY_H
#define LIBRARY_H



#pragma warning(push, 0)
	#include <QtCore/QDebug>
	#include <QtCore/QDir>

	#include <QtCore/QProcess>
	#include <QtCore/QQueue>
#pragma warning(pop)

#include <memory>

template <typename T>
using strong = std::shared_ptr<T>;

template <typename T>
using weak = std::weak_ptr<T>;

template <typename T>
using unique = std::unique_ptr<T>;

const QRegExp gRegExp_identifier = QRegExp("([A-Za-z_]\\w*)");
const QRegExp gRegExp_typeMod = QRegExp("(const|&|\\*|\\s)*");
const QRegExp gRegExp_typeId = QRegExp("(const|&|\\*|\\s|([A-Za-z_]\\w*))*");

#endif // LIBRARY_H
