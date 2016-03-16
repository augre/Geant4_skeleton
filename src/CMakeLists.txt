set(SIM_SOURCES main.cxx FlatSurfaceCurrent.cxx OpticalDetection.cxx AngleScorer.cxx DetectorConstruction.cxx DetectorMessenger.cxx ActionInitialization.cxx PencilBeamRunAction.cxx PencilBeamRun.cxx PencilBeamPrimaryGenerator.cxx PhysicsList.cxx)

add_executable(sim ${SIM_SOURCES})
target_link_libraries(sim ${Geant4_LIBRARIES})
install(TARGETS sim DESTINATION ${CMAKE_INSTALL_PREFIX})
