# Install script for directory: /home/matthias/Analysis/SSX13/SSX/PxlModules/systematics

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
  if(EXISTS "$ENV{DESTDIR}/home/matthias/.pxl-3.5/plugins/libBTagReweighting.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/home/matthias/.pxl-3.5/plugins/libBTagReweighting.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}/home/matthias/.pxl-3.5/plugins/libBTagReweighting.so"
         RPATH "")
  endif()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/home/matthias/.pxl-3.5/plugins/libBTagReweighting.so")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/home/matthias/.pxl-3.5/plugins" TYPE MODULE FILES "/home/matthias/Analysis/SSX13/SSX/PxlModules/build/systematics/libBTagReweighting.so")
  if(EXISTS "$ENV{DESTDIR}/home/matthias/.pxl-3.5/plugins/libBTagReweighting.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/home/matthias/.pxl-3.5/plugins/libBTagReweighting.so")
    file(RPATH_REMOVE
         FILE "$ENV{DESTDIR}/home/matthias/.pxl-3.5/plugins/libBTagReweighting.so")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/home/matthias/.pxl-3.5/plugins/libBTagReweighting.so")
    endif()
  endif()
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  if(EXISTS "$ENV{DESTDIR}/home/matthias/.pxl-3.5/plugins/libJetMETVariations.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/home/matthias/.pxl-3.5/plugins/libJetMETVariations.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}/home/matthias/.pxl-3.5/plugins/libJetMETVariations.so"
         RPATH "")
  endif()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/home/matthias/.pxl-3.5/plugins/libJetMETVariations.so")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/home/matthias/.pxl-3.5/plugins" TYPE MODULE FILES "/home/matthias/Analysis/SSX13/SSX/PxlModules/build/systematics/libJetMETVariations.so")
  if(EXISTS "$ENV{DESTDIR}/home/matthias/.pxl-3.5/plugins/libJetMETVariations.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/home/matthias/.pxl-3.5/plugins/libJetMETVariations.so")
    file(RPATH_REMOVE
         FILE "$ENV{DESTDIR}/home/matthias/.pxl-3.5/plugins/libJetMETVariations.so")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/home/matthias/.pxl-3.5/plugins/libJetMETVariations.so")
    endif()
  endif()
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  if(EXISTS "$ENV{DESTDIR}/home/matthias/.pxl-3.5/plugins/libMuonSF.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/home/matthias/.pxl-3.5/plugins/libMuonSF.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}/home/matthias/.pxl-3.5/plugins/libMuonSF.so"
         RPATH "")
  endif()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/home/matthias/.pxl-3.5/plugins/libMuonSF.so")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/home/matthias/.pxl-3.5/plugins" TYPE MODULE FILES "/home/matthias/Analysis/SSX13/SSX/PxlModules/build/systematics/libMuonSF.so")
  if(EXISTS "$ENV{DESTDIR}/home/matthias/.pxl-3.5/plugins/libMuonSF.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/home/matthias/.pxl-3.5/plugins/libMuonSF.so")
    file(RPATH_REMOVE
         FILE "$ENV{DESTDIR}/home/matthias/.pxl-3.5/plugins/libMuonSF.so")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/home/matthias/.pxl-3.5/plugins/libMuonSF.so")
    endif()
  endif()
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  if(EXISTS "$ENV{DESTDIR}/home/matthias/.pxl-3.5/plugins/libTopPtReweighting.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/home/matthias/.pxl-3.5/plugins/libTopPtReweighting.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}/home/matthias/.pxl-3.5/plugins/libTopPtReweighting.so"
         RPATH "")
  endif()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/home/matthias/.pxl-3.5/plugins/libTopPtReweighting.so")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/home/matthias/.pxl-3.5/plugins" TYPE MODULE FILES "/home/matthias/Analysis/SSX13/SSX/PxlModules/build/systematics/libTopPtReweighting.so")
  if(EXISTS "$ENV{DESTDIR}/home/matthias/.pxl-3.5/plugins/libTopPtReweighting.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/home/matthias/.pxl-3.5/plugins/libTopPtReweighting.so")
    file(RPATH_REMOVE
         FILE "$ENV{DESTDIR}/home/matthias/.pxl-3.5/plugins/libTopPtReweighting.so")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/home/matthias/.pxl-3.5/plugins/libTopPtReweighting.so")
    endif()
  endif()
endif()

