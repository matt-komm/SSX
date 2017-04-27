find_package(ROOT REQUIRED)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR} 
    ${PROJECT_SOURCE_DIR}/internal/TMVA/inc
    ${ROOT_INCLUDE_DIR}
    ${PROJECT_SOURCE_DIR}/internal/rapidjson
)

add_library(RootTreeWriter MODULE RootTree.cpp RootTreeWriter.cpp OutputStore.cpp)
target_link_libraries(RootTreeWriter ${PXL_LIBRARIES} ${ROOT_LIBRARIES})
install(
    TARGETS RootTreeWriter
    LIBRARY DESTINATION ${PXL_PLUGIN_INSTALL_PATH}
)

add_library(EventWeight MODULE EventWeight.cpp)
target_link_libraries(EventWeight ${PXL_LIBRARIES} ${ROOT_LIBRARIES})
install(
    TARGETS EventWeight
    LIBRARY DESTINATION ${PXL_PLUGIN_INSTALL_PATH}
)



add_library(LumiMask MODULE LumiMask.cpp)
target_link_libraries(LumiMask ${PXL_LIBRARIES} ${ROOT_LIBRARIES})
install(
    TARGETS LumiMask
    LIBRARY DESTINATION ${PXL_PLUGIN_INSTALL_PATH}
)

add_library(Splitter MODULE Splitter.cpp)
target_link_libraries(Splitter ${PXL_LIBRARIES} ${ROOT_LIBRARIES})
install(
    TARGETS Splitter
    LIBRARY DESTINATION ${PXL_PLUGIN_INSTALL_PATH}
)

add_library(TMVAEvaluation MODULE TMVAEvaluation.cpp)
target_link_libraries(TMVAEvaluation ${PXL_LIBRARIES} ${ROOT_LIBRARIES} TMVA)
install(
    TARGETS TMVAEvaluation
    LIBRARY DESTINATION ${PXL_PLUGIN_INSTALL_PATH}
)

add_library(PileUpReweighting MODULE PileUpReweighting.cpp)
target_link_libraries(PileUpReweighting ${PXL_LIBRARIES} ${ROOT_LIBRARIES})
install(
    TARGETS PileUpReweighting
    LIBRARY DESTINATION ${PXL_PLUGIN_INSTALL_PATH}
)


add_library(LumiInfo MODULE LumiInfo.cpp)
target_link_libraries(LumiInfo ${PXL_LIBRARIES} ${ROOT_LIBRARIES})
install(
    TARGETS LumiInfo
    LIBRARY DESTINATION ${PXL_PLUGIN_INSTALL_PATH}
)

add_library(Duplicator MODULE Duplicator.cpp)
target_link_libraries(Duplicator ${PXL_LIBRARIES})
install(
    TARGETS Duplicator
    LIBRARY DESTINATION ${PXL_PLUGIN_INSTALL_PATH}
)

add_library(JetCategory MODULE JetCategory.cpp)
target_link_libraries(JetCategory ${PXL_LIBRARIES})
install(
    TARGETS JetCategory
    LIBRARY DESTINATION ${PXL_PLUGIN_INSTALL_PATH}
)


add_library(Matching MODULE Matching.cpp)
target_link_libraries(Matching ${PXL_LIBRARIES})
install(
    TARGETS Matching
    LIBRARY DESTINATION ${PXL_PLUGIN_INSTALL_PATH}
)

add_library(SubAnalysis MODULE SubAnalysis.cpp)
target_link_libraries(SubAnalysis ${PXL_LIBRARIES})
install(
    TARGETS SubAnalysis
    LIBRARY DESTINATION ${PXL_PLUGIN_INSTALL_PATH}
)

