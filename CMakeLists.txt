# vim: sw=3 ts=3 expandtab smartindent
CMAKE_MINIMUM_REQUIRED(VERSION 2.8 FATAL_ERROR)

LIST(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake-modules)

INCLUDE(biicode/boost/setup)

ADD_BII_TARGETS()

INCLUDE(CodeCoverage)
INCLUDE(EnableExtraCompilerWarnings)
GLOBALLY_ENABLE_EXTRA_COMPILER_WARNINGS()

SET(CMAKE_EXPORT_COMPILE_COMMANDS 1)

IF (CMAKE_BUILD_TYPE STREQUAL "Debug")
   SET(CMAKE_C_FLAGS_DEBUG ${CMAKE_C_FLAGS_COVERAGE})
   SET(CMAKE_CXX_FLAGS_DEBUG ${CMAKE_CXX_FLAGS_COVERAGE})
ENDIF()

IF(APPLE)
   TARGET_COMPILE_OPTIONS(${BII_BLOCK_TARGET} INTERFACE "-std=c++1y -stdlib=libc++")
ELSEIF(WIN32 OR UNIX)
   TARGET_COMPILE_OPTIONS(${BII_BLOCK_TARGET} INTERFACE "-std=c++1y")
ENDIF()

SET(Boost_USE_STATIC_LIBS ON)
bii_find_boost()
#bii_find_boost(COMPONENTS uuid REQUIRED)
#TARGET_INCLUDE_DIRECTORIES(${BII_BLOCK_TARGET} INTERFACE ${Boost_INCLUDE_DIRS})
#TARGET_LINK_LIBRARIES(${BII_BLOCK_TARGET} INTERFACE ${Boost_LIBRARIES})

OPTION(GCC_LINK_TIME_OPTIMIZATION "Enable GCC Link Time Optimizations (LTO)" ON)
IF( CMAKE_BUILD_TYPE MATCHES Release AND GCC_LINK_TIME_OPTIMIZATION )
   MESSAGE(STATUS "Link-Time Optimization Enabled!")
   FIND_PROGRAM(CMAKE_GCC_AR NAMES ${_CMAKE_TOOLCHAIN_PREFIX}gcc-ar${_CMAKE_TOOLCHAIN_SUFFIX} HINTS ${_CMAKE_TOOLCHAIN_LOCATION} ENV PATH)
   FIND_PROGRAM(CMAKE_GCC_NM NAMES ${_CMAKE_TOOLCHAIN_PREFIX}gcc-nm HINTS ${_CMAKE_TOOLCHAIN_LOCATION})
   FIND_PROGRAM(CMAKE_GCC_RANLIB NAMES ${_CMAKE_TOOLCHAIN_PREFIX}gcc-ranlib HINTS ${_CMAKE_TOOLCHAIN_LOCATION})
   IF( CMAKE_GCC_AR AND CMAKE_GCC_NM AND CMAKE_GCC_RANLIB )
      SET( CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -flto=jobserver -fno-fat-lto-objects" )
      SET( CMAKE_AR "${CMAKE_GCC_AR}" )
      SET( CMAKE_NM "${CMAKE_GCC_NM}" )
      SET( CMAKE_RANLIB "${CMAKE_GCC_RANLIB}" )
   ELSE()
      MESSAGE( WARNING "GCC indicates LTO support, but binutils wrappers could not be found. Disabling LTO." )
   ENDIF()
ENDIF()
