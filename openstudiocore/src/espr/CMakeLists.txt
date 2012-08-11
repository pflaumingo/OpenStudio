SET( target_name openstudio_espr )

SET( ${target_name}_src
  ESPRAPI.hpp
  mainpage.hpp
  ForwardTranslator.hpp
  ForwardTranslator.cpp
  ReverseTranslator.hpp
  ReverseTranslator.cpp
  MapEnvelope.cpp
  MapSchedules.cpp
  regexp.cpp
  Espr3d.cpp
  EsprDef.cpp
  regexp.cpp
  RootEnvironment.cpp
  TBuilding.cpp
  TConstruction.cpp
  TESPR.cpp
  TFileUtilities.cpp
  TGlazing.cpp
  TMaterial.cpp
  TZone.cpp
)

SET( ${target_name}_test_src
  Test/ESPRFixture.hpp
  Test/ESPRFixture.cpp
  Test/ForwardTranslator_GTest.cpp
  Test/ReverseTranslator_GTest.cpp
)

SET( ${target_name}_swig_src
  ESPR.i
)

SET( ${target_name}_depends
  ${Boost_LIBRARIES}
  ${CMAKE_THREAD_LIBS}
  ${QT_LIBS}
  openstudio_utilities
  openstudio_model
  openstudio_energyplus
  zkexpat
  boost_log
)

ADD_LIBRARY( ${target_name} SHARED ${${target_name}_src} )
TARGET_LINK_LIBRARIES( ${target_name} ${${target_name}_depends} )
AddPCH(${target_name})

#IF( NOT APPLE )
INSTALL(TARGETS ${target_name} 
  RUNTIME DESTINATION bin 
  LIBRARY DESTINATION lib )
#ENDIF()

CREATE_SRC_GROUPS( "${${target_name}_src}" )
CREATE_SRC_GROUPS( "${${target_name}_test_src}" )
CREATE_SRC_GROUPS( "${${target_name}_swig_src}" )

CREATE_TEST_TARGETS( ${target_name} "${${target_name}_test_src}" "${${target_name}_depends}")
IF(BUILD_TESTING)
  ADD_DEPENDENCIES(${target_name}_tests openstudio_espr_resources)
ENDIF()

MAKE_SWIG_TARGET( OpenStudioESPR espr "${CMAKE_CURRENT_SOURCE_DIR}/ESPR.i" "${${target_name}_swig_src}" ${target_name} "${target_name}" )

add_executable(ESPRToIdf ESPRToIdf.cpp)
AddPCH(ESPRToIdf)

TARGET_LINK_LIBRARIES( ESPRToIdf
  ${${target_name}_depends}
  openstudio_espr
)

INSTALL(TARGETS ESPRToIdf
    BUNDLE DESTINATION . 
    RUNTIME DESTINATION bin 
    )
