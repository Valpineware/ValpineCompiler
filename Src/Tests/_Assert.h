//==================================================================================================================|
// Created 2015.03.17by Daniel L. Watkins
//
// Copyright (C) 2015 Valpineware
// This file is licensed under the MIT License.
//==================================================================================================================|

#ifndef _ext_Assert_H
#define _ext_Assert_H

#include <gtest\gtest.h>

#include <QtCore/QString>

namespace ext
{
	/**
	 * \brief Custom assert wrapper for convenience.
	 */
	class Assert
	{ 
	public:
		/**
		 * If set to true, asserts will call qFatal to allow a debugger to break exactly where the assert
		 * was triggered. If set to false, the standard Google Test framework asserts will be used
		 */
		static void setFatalOnAssert(bool fatalOnAssert) { mFatalOnAssert = fatalOnAssert; }

		/**
		 * Asserts if \what evaluates to false.
		 */
		template<typename T>
		static void True(const T &what)
		{
			if (mFatalOnAssert)
			{
				if (static_cast<bool>(what) == false)
					qFatal("Not true");
			}
			else
				ASSERT_TRUE(what);
		}


		/**
		 * Asserts if \what evaluates to true.
		 */
		template<typename T>
		static void False(const T &what)
		{
			if (mFatalOnAssert)
			{
				if (static_cast<bool>(what) == true)
					qFatal("Not false");
			}
			else
				ASSERT_FALSE(what);
		}


		/**
		 * Asserts if \p a does not equal \p b
		 */
		template<typename A, typename B>
		static void Eq(const A &a, const B &b)
		{
			if (mFatalOnAssert)
			{
				if (!(a == b))
					qFatal("Unequal");
			}
			else
				Assert::Eq(a, b);
		}


		/**
		 * Asserts if the characters in \p a do not exactly match those in \p b.
		 */
		static void EqStr(const QString &a, const QString &b)
		{

			if (mFatalOnAssert)
			{
				if (a != b)
					qFatal("Unequal");
			}
			else
				Assert::Eq(a, b);
		}


		/**
		 * Asserts if \p what is not null.
		 */
		template<typename T>
		static void Null(const T *what)
		{
			if (mFatalOnAssert)
			{
				if (what != nullptr)
					qFatal("Is NOT nullptr");
			}
			else
				ASSERT_FALSE(static_cast<bool>(what)) << "Nullptr NOT detected";
		}


		/**
		 * Asserts if \p what is null.
		 */
		template<typename T>
		static void NotNull(const T *what)
		{
			if (mFatalOnAssert)
			{
				if (what == nullptr)
					qFatal("Is nullptr");
			}
			else
				ASSERT_TRUE(static_cast<bool>(what)) << "Nullptr detected";
		}

	private:
		static bool mFatalOnAssert;
	};
}

#endif
