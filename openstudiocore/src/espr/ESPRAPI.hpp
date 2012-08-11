#ifndef __ESPR_API_HPP__
#define __ESPR_API_HPP__

#if _WIN32 || _MSC_VER

#ifdef openstudio_espr_EXPORTS
#define ESPR_API __declspec(dllexport)
#else
#define ESPR_API __declspec(dllimport)
#endif
#else
#define ESPR_API
#endif

#endif
