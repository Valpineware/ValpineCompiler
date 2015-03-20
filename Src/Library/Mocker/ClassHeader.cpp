#include "ClassHeader.h"


namespace vc { namespace mocker
{

	ClassHeader::ClassHeader(QString &classID, int scopeLevel)
	{
		mClassID = classID;
		mScopeLevel = scopeLevel;
	}

	QVector<QString> ClassHeader::buildClass()
	{
		QVector<QString> headerClass;
		headerClass.append(Utility::createTabs(mScopeLevel) + "class " + mClassID);
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

		//TODO!!! Refactor this :D --thanks 
		/*//add private members
		mScopeLevel += 1;
		for (QString member : mPrivateMembers)
		{
			headerClass.append(Utility::createTabs(mScopeLevel) + member + ";");
		}

		//add protected members
		headerClass.append(Utility::createTabs(mScopeLevel - 1) + "protected:");
		for (QString member : mProtectedMembers)
		{
			headerClass.append(Utility::createTabs(mScopeLevel) + member + ";");
		}

		//add public memebers
		headerClass.append(Utility::createTabs(mScopeLevel - 1) + "public:");
		for (QString member : mPublicMembers)
		{
			headerClass.append(Utility::createTabs(mScopeLevel) + member + ";");
		}*/

		//finish class
		headerClass.append("};");
	}
	


}}