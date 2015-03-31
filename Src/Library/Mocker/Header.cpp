#include "Header.h"

namespace vc { namespace mocker
{
	Header::Header(int scopeLevel)
	{
		mScopeLevel = scopeLevel;
	}

	void Header::addInclude(QString &include)
	{
		mIncludes.append(include);
	}

	void Header::addClass(QString &className)
	{
		ClassHeader * classHeader  = new ClassHeader(className, mScopeLevel);
		mClassHeaders.append(classHeader);
	}

	void Header::addFunctionDec(QString &functionDec)
	{
		mFunctionDecs.append(functionDec);
	}

	void Header::addClassMember(const QString &classID, QString &memberDec, const ScopeState state)
	{
		//search for class Dec
		for (ClassHeader *classHeader : mClassHeaders)
		{
			if (classHeader->getClassID() == classID)
			{
				//add member dec
				if (state == scopePrivate)
				{
					classHeader->addPrivateMember(memberDec);
				}
				else if (state == scopePublic)
				{
					classHeader->addPublicMember(memberDec);
				}
				else if (state == scopeProtected)
				{
					classHeader->addProtectedMember(memberDec);
				}
				else
				{
					//shouldn't happen
					classHeader->addPublicMember(memberDec);
				}

				//leave method
				return;
			}
		}		
	}


	void Header::buildHeader(QTextStream &outStream)
	{
		Utility::vectorToStream(outStream, mIncludes);
		Utility::vectorToStream(outStream, mFunctionDecs);

		//add class declerations
		for (ClassHeader *classHeader : mClassHeaders)
		{
			classHeader->buildClass(outStream);
		}

	}

}}