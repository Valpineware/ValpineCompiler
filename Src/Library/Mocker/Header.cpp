#include "Header.h"

namespace vc { namespace mocker
{
	Header::Header(int scopeLevel)
	{
		mScopeLevel = scopeLevel;
	}


	void Header::addClass(QString &className)
	{
		ClassHeader classHeader(className, mScopeLevel);
		mClassHeaders.append(classHeader);
	}

	void Header::addFunctionDec(QString &functionDec)
	{
		mFunctionDecs.append(functionDec);
	}

	void Header::addClassMember(QString &classID, QString &memberDec, ScopeState state)
	{
		//search for class Dec
		for (ClassHeader classHeader : mClassHeaders)
		{
			if (classHeader.getClassID == classID)
			{
				//add member dec
				if (state == scopePrivate)
				{
					classHeader.addPrivateMember(memberDec);
				}
				else if (state == scopePublic)
				{
					classHeader.addPublicMember(memberDec);
				}
				else if (state == scopeProtected)
				{
					classHeader.addProtectedMember(memberDec);
				}
				else
				{
					//shouldn't happen
					classHeader.addPublicMember(memberDec);
				}

				//leave method
				return;
			}
		}		
	}


	QVector<QString> Header::buildHeader()
	{
		QVector<QString> header;
		header += mFunctionDecs;

		//add class declerations
		for (ClassHeader classHeader : mClassHeaders)
		{
			header += classHeader.buildClass();
		}

	}

}}