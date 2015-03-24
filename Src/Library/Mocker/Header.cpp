#include "Header.h"

namespace vc { namespace mocker
{
	Header::Header(int scopeLevel)
	{
		mScopeLevel = scopeLevel;
	}


	void Header::addClass(const QString &className)
	{
		ClassHeader classHeader(className, mScopeLevel);
		mClassHeaders.append(classHeader);
	}

	void Header::addFunctionDec(const QString &functionDec)
	{
		mFunctionDecs.append(functionDec);
	}

	void Header::addClassMember(const QString &classID, const QString &memberDec, const ScopeState state)
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


	QVector<const QString> Header::buildHeader()
	{
		QVector<const QString> header;
		header += mFunctionDecs;

		//add class declerations
		for (ClassHeader classHeader : mClassHeaders)
		{
			header += classHeader.buildClass();
		}

	}

}}