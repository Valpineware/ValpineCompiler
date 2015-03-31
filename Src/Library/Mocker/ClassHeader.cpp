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
		
		
		//add protected members
		outStream << Utility::createTabs(mScopeLevel) << "protected:" << "\n";
		Utility::vectorToStream(outStream, mProtectedMembers);

		//add public members
		outStream << Utility::createTabs(mScopeLevel) << "public:" << "\n";
		Utility::vectorToStream(outStream, mProtectedMembers);

		//finish class
		outStream << "};";
	}
	


}}