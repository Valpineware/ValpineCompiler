//==================================================================================================================|
// Created 2015.02.08 by Daniel L. Watkins
//
// Copyright (C) 2015 Valpineware
// This file is licensed under the MIT License.
//==================================================================================================================|

#ifndef _vc_graph_Utility_h
#define _vc_graph_Utility_h

#include <Library.h>

#include "Class.h"

namespace vc { namespace graph
{
	class TypeExpression;

	/**
	 * @brief 
	 */
	class Utility
	{
	public:
		static void breakUpByWhitespace(const QString &what, QStringList &list);

		static bool parseTypeExpression(QStringListIterator &i, TypeExpression &typeExpression);

		/**
		 * @returns true if \what looks like an id and is not a reserved id.
		 */
		static bool couldBeIdentifier(const QString &what);

		/**
		 * @returns true if \p what looks like an id and is not a reserved id (except for reserved types).
		 */
		static bool couldBeTypeIdentifier(const QString &what);

		static bool couldBeNumericConstant(const QString &what);

		static bool isReservedWord_control(const QString &what);

		/**
		 * Puts a space before and after every occurrence of an operator. Compound operators contain multiple 
		 */
		static void breakUpOperators(QString &what);


		static Class::AccessType accessTypeForString(const QString what);

		template <template<typename> class T>
		static QString flatten(const T<QString> &list, const QString &spacer="")
		{
			QString buffer;
			buffer.reserve(3 * list.count());

			for (int i=0; i<list.count(); i++)
			{
				if (i == list.count()-1)
					buffer.append(list.at(i));
				else
					buffer.append(list.at(i)+spacer);
			}

			return buffer;
		}


		struct ReservedIds
		{
			QStringList general, types, control, typeDeclarators, access, casting;

			bool anyContain(const QString &str)
			{
				return	(general.contains(str) ||
						types.contains(str) ||
						control.contains(str) ||
						typeDeclarators.contains(str) ||
						access.contains(str) ||
						casting.contains(str));
			}
		};
	};
}}

#endif
