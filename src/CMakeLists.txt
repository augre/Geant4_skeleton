set(SIM_SOURCES main.cxx FlatSurfaceCurrent.cxx OpticalDetection.cxx AngleScorer.cxx DetectorConstruction.cxx DetectorMessenger.cxx ActionInitialization.cxx PencilBeamRunAction.cxx PencilBeamRun.cxx PencilBeamPrimaryGenerator.cxx PhysicsList.cxx)


add_executable(sim ${SIM_SOURCES})
add_library(LinkedList SHARED LinkedList.c)
target_link_libraries(sim ${Geant4_LIBRARIES})
target_link_libraries(sim LinkedList)
install(TARGETS sim DESTINATION ${PROJECT_SOURCE_DIR})
