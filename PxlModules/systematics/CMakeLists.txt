find_package(ROOT REQUIRED)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR} 
    ${ROOT_INCLUDE_DIR}
)

add_library(BTagReweighting MODULE BTagReweighting.cpp BTagCalibrationStandalone.cpp)
target_link_libraries(BTagReweighting ${PXL_LIBRARIES} ${ROOT_LIBRARIES})
install(
    TARGETS BTagReweighting
    LIBRARY DESTINATION ${PXL_PLUGIN_INSTALL_PATH}
)

#add_executable(btag-test
#    BTagCalibrationStandalone.cpp
#    test.cpp
#)
#target_link_libraries(btag-test ${ROOT_LIBRARIES})

add_library(JetMETVariations MODULE JetMETVariations.cpp)
target_link_libraries(JetMETVariations ${PXL_LIBRARIES} ${ROOT_LIBRARIES})
install(
    TARGETS JetMETVariations
    LIBRARY DESTINATION ${PXL_PLUGIN_INSTALL_PATH}
)


add_library(MuonSF MODULE MuonSF.cpp)
target_link_libraries(MuonSF ${PXL_LIBRARIES} ${ROOT_LIBRARIES})
install(
    TARGETS MuonSF
    LIBRARY DESTINATION ${PXL_PLUGIN_INSTALL_PATH}
)

add_library(TopPtReweighting MODULE TopPtReweighting.cpp)
target_link_libraries(TopPtReweighting ${PXL_LIBRARIES} ${ROOT_LIBRARIES})
install(
    TARGETS TopPtReweighting
    LIBRARY DESTINATION ${PXL_PLUGIN_INSTALL_PATH}
)

