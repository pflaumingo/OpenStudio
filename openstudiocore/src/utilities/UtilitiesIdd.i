#ifndef UTILITIES_UTILITIESIDD_I
#define UTILITIES_UTILITIESIDD_I

#ifdef SWIGPYTHON
%module openstudioutilitiesidd
#endif


#define UTILITIES_API
#define extern extern

%include <utilities/core/CommonInclude.i>
%import <utilities/core/CommonImport.i>
%import <utilities/UtilitiesCore.i>
%import <utilities/UtilitiesUnits.i>

%include <utilities/idd/Idd.i>

#endif

