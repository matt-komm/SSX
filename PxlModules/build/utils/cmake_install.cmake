# Install script for directory: /home/matthias/Analysis/SSX13/SSX/PxlModules/utils

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  if(EXISTS "$ENV{DESTDIR}/home/matthias/.pxl-3.5/plugins/libRootTreeWriter.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/home/matthias/.pxl-3.5/plugins/libRootTreeWriter.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}/home/matthias/.pxl-3.5/plugins/libRootTreeWriter.so"
         RPATH "")
  endif()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/home/matthias/.pxl-3.5/plugins/libRootTreeWriter.so")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/home/matthias/.pxl-3.5/plugins" TYPE MODULE FILES "/home/matthias/Analysis/SSX13/SSX/PxlModules/build/utils/libRootTreeWriter.so")
  if(EXISTS "$ENV{DESTDIR}/home/matthias/.pxl-3.5/plugins/libRootTreeWriter.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/home/matthias/.pxl-3.5/plugins/libRootTreeWriter.so")
    file(RPATH_REMOVE
         FILE "$ENV{DESTDIR}/home/matthias/.pxl-3.5/plugins/libRootTreeWriter.so")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/home/matthias/.pxl-3.5/plugins/libRootTreeWriter.so")
    endif()
  endif()
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  if(EXISTS "$ENV{DESTDIR}/home/matthias/.pxl-3.5/plugins/libEventWeight.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/home/matthias/.pxl-3.5/plugins/libEventWeight.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}/home/matthias/.pxl-3.5/plugins/libEventWeight.so"
         RPATH "")
  endif()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/home/matthias/.pxl-3.5/plugins/libEventWeight.so")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/home/matthias/.pxl-3.5/plugins" TYPE MODULE FILES "/home/matthias/Analysis/SSX13/SSX/PxlModules/build/utils/libEventWeight.so")
  if(EXISTS "$ENV{DESTDIR}/home/matthias/.pxl-3.5/plugins/libEventWeight.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/home/matthias/.pxl-3.5/plugins/libEventWeight.so")
    file(RPATH_REMOVE
         FILE "$ENV{DESTDIR}/home/matthias/.pxl-3.5/plugins/libEventWeight.so")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/home/matthias/.pxl-3.5/plugins/libEventWeight.so")
    endif()
  endif()
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  if(EXISTS "$ENV{DESTDIR}/home/matthias/.pxl-3.5/plugins/libLumiMask.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/home/matthias/.pxl-3.5/plugins/libLumiMask.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}/home/matthias/.pxl-3.5/plugins/libLumiMask.so"
         RPATH "")
  endif()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/home/matthias/.pxl-3.5/plugins/libLumiMask.so")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/home/matthias/.pxl-3.5/plugins" TYPE MODULE FILES "/home/matthias/Analysis/SSX13/SSX/PxlModules/build/utils/libLumiMask.so")
  if(EXISTS "$ENV{DESTDIR}/home/matthias/.pxl-3.5/plugins/libLumiMask.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/home/matthias/.pxl-3.5/plugins/libLumiMask.so")
    file(RPATH_REMOVE
         FILE "$ENV{DESTDIR}/home/matthias/.pxl-3.5/plugins/libLumiMask.so")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/home/matthias/.pxl-3.5/plugins/libLumiMask.so")
    endif()
  endif()
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  if(EXISTS "$ENV{DESTDIR}/home/matthias/.pxl-3.5/plugins/libSplitter.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/home/matthias/.pxl-3.5/plugins/libSplitter.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}/home/matthias/.pxl-3.5/plugins/libSplitter.so"
         RPATH "")
  endif()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/home/matthias/.pxl-3.5/plugins/libSplitter.so")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/home/matthias/.pxl-3.5/plugins" TYPE MODULE FILES "/home/matthias/Analysis/SSX13/SSX/PxlModules/build/utils/libSplitter.so")
  if(EXISTS "$ENV{DESTDIR}/home/matthias/.pxl-3.5/plugins/libSplitter.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/home/matthias/.pxl-3.5/plugins/libSplitter.so")
    file(RPATH_REMOVE
         FILE "$ENV{DESTDIR}/home/matthias/.pxl-3.5/plugins/libSplitter.so")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/home/matthias/.pxl-3.5/plugins/libSplitter.so")
    endif()
  endif()
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  if(EXISTS "$ENV{DESTDIR}/home/matthias/.pxl-3.5/plugins/libTMVAEvaluation.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/home/matthias/.pxl-3.5/plugins/libTMVAEvaluation.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}/home/matthias/.pxl-3.5/plugins/libTMVAEvaluation.so"
         RPATH "")
  endif()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/home/matthias/.pxl-3.5/plugins/libTMVAEvaluation.so")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/home/matthias/.pxl-3.5/plugins" TYPE MODULE FILES "/home/matthias/Analysis/SSX13/SSX/PxlModules/build/utils/libTMVAEvaluation.so")
  if(EXISTS "$ENV{DESTDIR}/home/matthias/.pxl-3.5/plugins/libTMVAEvaluation.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/home/matthias/.pxl-3.5/plugins/libTMVAEvaluation.so")
    file(RPATH_REMOVE
         FILE "$ENV{DESTDIR}/home/matthias/.pxl-3.5/plugins/libTMVAEvaluation.so")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/home/matthias/.pxl-3.5/plugins/libTMVAEvaluation.so")
    endif()
  endif()
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  if(EXISTS "$ENV{DESTDIR}/home/matthias/.pxl-3.5/plugins/libPileUpReweighting.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/home/matthias/.pxl-3.5/plugins/libPileUpReweighting.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}/home/matthias/.pxl-3.5/plugins/libPileUpReweighting.so"
         RPATH "")
  endif()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/home/matthias/.pxl-3.5/plugins/libPileUpReweighting.so")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/home/matthias/.pxl-3.5/plugins" TYPE MODULE FILES "/home/matthias/Analysis/SSX13/SSX/PxlModules/build/utils/libPileUpReweighting.so")
  if(EXISTS "$ENV{DESTDIR}/home/matthias/.pxl-3.5/plugins/libPileUpReweighting.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/home/matthias/.pxl-3.5/plugins/libPileUpReweighting.so")
    file(RPATH_REMOVE
         FILE "$ENV{DESTDIR}/home/matthias/.pxl-3.5/plugins/libPileUpReweighting.so")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/home/matthias/.pxl-3.5/plugins/libPileUpReweighting.so")
    endif()
  endif()
endif()

