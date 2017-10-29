project(PyFit)
cmake_minimum_required(VERSION 2.8)
set(CMAKE_MODULE_PATH  "${CMAKE_CURRENT_SOURCE_DIR}" "${CMAKE_MODULE_PATH}")


macro(copy_file_if_changed in_file out_file target)  
    	add_custom_command (
    		TARGET     ${target}
    		POST_BUILD
    		COMMAND    ${CMAKE_COMMAND}
    		ARGS       -E copy_if_different ${in_file} ${out_file}
    		COMMENT "Copying file: ${in_file} to: ${out_file}"
    	)
endmacro(copy_file_if_changed)


include_directories(${PROJECT_SOURCE_DIR})
include_directories(${PROJECT_BINARY_DIR})

find_package(ROOT)

set(CMAKE_CXX_FLAGS "-Wextra -Wall -pedantic ${ROOT_CFLAGS} -Wno-long-long -std=c++11 -Wno-unused-parameter")
include_directories(${ROOT_INCLUDE_DIR})

set(CLASSHEADERS 
    PyFit.hpp
    PyUnfold.hpp
    PyUtils.hpp
)

set_source_files_properties(${PROJECT_BINARY_DIR}/dict.C PROPERTIES GENERATED TRUE)
add_custom_target(generatedicts ALL ${ROOT_DICT_EXECUTABLE} 
    -f ${PROJECT_BINARY_DIR}/dict.C 
    -c ${CLASSHEADERS} LinkDef.h 
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

add_library(pyfit MODULE 
    PyFit.cpp
    PyUnfold.cpp
    PyUtils.cpp
    dict.C
)
target_link_libraries(pyfit ${ROOT_LIBRARIES} -lMinuit2 -lXMLParser)
add_dependencies(pyfit generatedicts)
install(TARGETS pyfit LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX})

copy_file_if_changed(${CMAKE_CURRENT_SOURCE_DIR}/testPyFit.py ${CMAKE_CURRENT_BINARY_DIR}/testPyFit.py pyfit)
copy_file_if_changed(${CMAKE_CURRENT_SOURCE_DIR}/testPyUnfold.py ${CMAKE_CURRENT_BINARY_DIR}/testPyUnfold.py pyfit)
copy_file_if_changed(${CMAKE_CURRENT_SOURCE_DIR}/pyfit.py ${CMAKE_CURRENT_BINARY_DIR}/pyfit.py pyfit)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/pyfit.py DESTINATION ${CMAKE_INSTALL_PREFIX})
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/dict_rdict.pcm DESTINATION ${CMAKE_INSTALL_PREFIX})

