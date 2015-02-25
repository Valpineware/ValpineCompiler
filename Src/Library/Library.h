#ifndef LIBRARY_H
#define LIBRARY_H

#pragma warning(push, 0)
	#include <QtCore/QDebug>
	#include <QtCore/QDir>
	
	#include <QtCore/QProcess>

	#include <QtCore/QQueue>
	#include <QtCore/QList>
	#include <QtCore/QVector>
#pragma warning(pop)

#include <memory>

/**
 * Use at your own risk. The Valpine language will have this built in a safely.
 */
#define STATIC_BLOCK_UNSAFE(name, body) struct Init##name { Init##name() { body } }; static Init##name _staticBlock_##name

namespace vc
{
	template <typename T>
	using strong = std::shared_ptr<T>;

	template <typename T>
	using weak = std::weak_ptr<T>;

	template <typename T>
	using unique = std::unique_ptr<T>;

	const QRegExp gRegExp_numericConstant = QRegExp("[0-9]+");
	const QRegExp gRegExp_identifier = QRegExp("([A-Za-z_]\\w*)");
	const QRegExp gRegExp_typeMod = QRegExp("(const|&|\\*|\\s)*");
	const QRegExp gRegExp_typeId = QRegExp("(const|&|\\*|\\s|([A-Za-z_]\\w*))*");
	const QRegExp gRegExp_operatorChar = QRegExp("[!%()\\^&*|:\\-+=<>?/,]");

	/**
	 * Convenience QListIterator factory. Allows for use with the auto keyword. For example:
	 * auto myIter = vc::makeIter(myList);
	 */
	template<typename T>
	QListIterator<T> makeIter(const QList<T> &list)
	{
		return QListIterator<T>(list);
	}

	/**
	 * Convenience QVectorIterator factory. Allows for use with the auto keyword. For example:
	 * auto myIter = vc::makeIter(myVector);
	 */
	template<typename T>
	QVectorIterator<T> makeIter(const QVector<T> &list)
	{
		return QVectorIterator<T>(list);
	}
}

#endif
