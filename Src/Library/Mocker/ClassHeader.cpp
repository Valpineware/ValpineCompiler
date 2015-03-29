#include "ClassHeader.h"


namespace vc { namespace mocker
{

	ClassHeader::ClassHeader(QString &classID, int scopeLevel)
	{
		mClassID = classID;
		mScopeLevel = scopeLevel;
	}

	void ClassHeader::buildClass(QTextStream &outStream)
	{
		outStream << Utility::createTabs(mScopeLevel) << "class " << mClassID << "\n";
		outStream << Utility::createTabs(mScopeLevel) << "{" << "\n";

		//add private members
		outStream << Utility::createTabs(mScopeLevel) << "private:" << "\n";
		
		Utility::vectorToStream(outStream, mPrivateMembers);
		
		/*
		//add protected members
		headerClass.append(Utility::createTabs(mScopeLevel) + "protected");
		headerClass += mProtectedMembers;

		//add public members
		headerClass.append(Utility::createTabs(mScopeLevel) + "public");
		headerClass += mPublicMembers;

		//finish class
		headerClass.append("};");

		return headerClass;*/
	}
	


}}