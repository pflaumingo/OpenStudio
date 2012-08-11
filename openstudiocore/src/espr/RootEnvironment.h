#ifndef ROOTENVIRONMENT_H_
#define ROOTENVIRONMENT_H_
#include "stdafx.h"

#include <string>
class TRootEnvironment
{
public:
    static TRootEnvironment* Instance();
    std::string sRootFolder;
protected:
    TRootEnvironment();
    TRootEnvironment(const TRootEnvironment&);
    TRootEnvironment& operator= (const TRootEnvironment&);
private:
    static TRootEnvironment* pinstance;
};

#endif /*TRootEnvironment_H_*/
