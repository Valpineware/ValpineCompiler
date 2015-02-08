#ifndef _vc_Tests_H
#define _vc_Tests_H

#include <gtest/gtest.h>

#include <QtCore/QDebug>
#include <QtCore/QString>

const QString gTestDir = "./Tests/";

/**
 * First #define a class identifier. Then declare this followed
 * by a brace enclosed class declaration.
 */
#define TEST_CLASS \
	class CLASS : public ::testing::Test

/**
 * After declaring a TEST_CLASS in the same file, declare single
 * test cases with TEST_CASE(testName) followed by a brace enclosed
 * function declaration.
 */
#define TEST_CASE(name) \
	TEST_F(CLASS, name)


#define FOR_TIMES(i, count) for (int i=0; i<count; ++i)


#define ASSERT_NULL(what) ASSERT_TRUE(what == nullptr)
#define ASSERT_NOT_NULL(what) ASSERT_FALSE(what == nullptr)

void assertEqStr(const QString &exp, const QString &actual);
#define EXPECT_EQ_STR(expected, actual) assertEqStr(expected, actual);

#endif
