PROJECT(IVOL4D)

#---------------------------------------------------------

CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

SET(NRRD_LIBDIR "~/programs/ijk/lib")

#---------------------------------------------------------

IF (NOT CMAKE_BUILD_TYPE)
  SET (CMAKE_BUILD_TYPE Release CACHE STRING 
       "Default build type: Release" FORCE)
ENDIF (NOT CMAKE_BUILD_TYPE)

LINK_DIRECTORIES("${NRRD_LIBDIR}")
LINK_LIBRARIES(NrrdIO z)

ADD_EXECUTABLE(ivol4D ivol4D.cxx)

ADD_EXECUTABLE(gen_ivol4D gen_ivol4D.cxx)

ADD_CUSTOM_TARGET(tar WORKING_DIRECTORY . COMMAND tar cvfh ivol4D.tar *.cxx *.h *.txx CMakeLists.txt ivol4D_doxygen.config)

ADD_CUSTOM_TARGET(doc COMMAND doxygen ivol4D_doxygen.config)

