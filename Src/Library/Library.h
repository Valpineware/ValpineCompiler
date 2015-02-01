#ifndef LIBRARY_H
#define LIBRARY_H



#pragma warning(push, 0)
	#include <QtCore/QDebug>
	#include <QtCore/QDir>

	#include <QtCore/QProcess>
#pragma warning(pop)

#include <memory>

template <typename T>
using strong = std::shared_ptr<T>;

template <typename T>
using weak = std::weak_ptr<T>;

template <typename T>
using unique = std::unique_ptr<T>;

#endif // LIBRARY_H
