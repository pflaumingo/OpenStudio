#ifndef ESPR_I
#define ESPR_I

#define UTILITIES_API
#define ESPR_API

%include <utilities/core/CommonInclude.i>
%import <utilities/core/CommonImport.i>
%import <utilities/Utilities.i>
%import <model/Model.i>

%{
  #include <ESPR/ReverseTranslator.hpp>
  #include <ESPR/ForwardTranslator.hpp>
  using namespace openstudio::ESPR;
  using namespace openstudio;
  
  #include <model/Model.hpp>
  #include <model/ModelObject.hpp>
  
  #include <QDomDocument>
  #include <QDomElement>
%}

#ifdef SWIGCSHARP
%rename(ESPRReverseTranslator) openstudio::ESPR::ReverseTranslator;
%rename(ESPRForwardTranslator) openstudio::ESPR::ForwardTranslator;
#endif

%include <ESPR/ReverseTranslator.hpp>
%include <ESPR/ForwardTranslator.hpp>

#endif //ESPR_I 
