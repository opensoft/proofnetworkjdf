include(CMakeFindDependencyMacro)

list(APPEND CMAKE_PREFIX_PATH "${CMAKE_CURRENT_LIST_DIR}/3rdparty")
find_dependency(Qt5Core CONFIG REQUIRED)
find_dependency(Qt5Gui CONFIG REQUIRED)
find_dependency(Qt5Network CONFIG REQUIRED)
find_dependency(Qt5Xml CONFIG REQUIRED)
find_dependency(ProofNetwork CONFIG REQUIRED)
list(REMOVE_AT CMAKE_PREFIX_PATH -1)

if(NOT TARGET Proof::NetworkXJdf)
    include("${CMAKE_CURRENT_LIST_DIR}/ProofNetworkXJdfTargets.cmake")
endif()
