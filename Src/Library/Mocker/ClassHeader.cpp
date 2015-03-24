#include "ClassHeader.h"


namespace vc { namespace mocker
{

	ClassHeader::ClassHeader(const QString &classID, int scopeLevel)
	{
		mClassID = &classID;
		mScopeLevel = scopeLevel;
	}

	QVector<const QString> ClassHeader::buildClass()
	{
		QVector<const QString> headerClass;
		headerClass.append(Utility::createTabs(mScopeLevel) + "class " + *mClassID);
		headerClass.append(Utility::createTabs(mScopeLevel) + "{");

		//add private members
		headerClass.append(Utility::createTabs(mScopeLevel) + "private:");
		headerClass += mPrivateMembers;
		
		//add protected members
		headerClass.append(Utility::createTabs(mScopeLevel) + "protected");
		headerClass += mProtectedMembers;

		//add public members
		headerClass.append(Utility::createTabs(mScopeLevel) + "public");
		headerClass += mPublicMembers;

		//finish class
		headerClass.append("};");
	}
	


}}