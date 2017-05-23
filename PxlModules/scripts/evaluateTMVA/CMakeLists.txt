find_package(ROOT REQUIRED)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR} 
    ${PROJECT_SOURCE_DIR}/internal/TMVA/inc
    ${PROJECT_SOURCE_DIR}/utils
    ${ROOT_INCLUDE_DIR}
    ${PROJECT_SOURCE_DIR}/internal/rapidjson
    ${PROJECT_SOURCE_DIR}/internal/tinyxml2
)

add_executable(evaluateTMVA
    evaluateTMVA.cc
)
target_link_libraries(evaluateTMVA tinyxml2 ${ROOT_LIBRARIES} TMVA)


