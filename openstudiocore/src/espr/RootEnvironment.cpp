#include <stdlib.h>// for MAX_PATH
#include <direct.h>
#include "stdafx.h"
#include "RootEnvironment.h"
#include "TFileUtilities.h"

TRootEnvironment* TRootEnvironment::pinstance = 0;// initialize pointer

//Should change this if used for multithreaded!!
TRootEnvironment* TRootEnvironment::Instance ()
{
    static TRootEnvironment inst;
    return &inst;
}

TRootEnvironment::TRootEnvironment()
{
    char* buffer = NULL;
    _getcwd(buffer, 512);
    sRootFolder = std::string(buffer);
 #ifdef DEBUG
    std::cout << sRootFolder <<std::endl;
 #endif
}
