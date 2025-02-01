cmake_minimum_required(VERSION 3.18)
project(pygbs LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)

add_subdirectory(nlopt)

# Trouver pybind11 (scikit-build va injecter les chemins si pybind11 est installé via pip/conda).
find_package(pybind11 REQUIRED)
find_package(Eigen3 REQUIRED)
find_package(Boost REQUIRED)
message(STATUS "Boost_INCLUDE_DIR: " ${Boost_INCLUDE_DIR})
# find_package(NLopt REQUIRED)
# TODO add Confiure to gbs install
find_package(Gbs REQUIRED)
message(STATUS "GBS_INCLUDE_DIR: " ${GBS_INCLUDE_DIR})
message(STATUS "nlopt_lib" ${CMAKE_})
# message(STATUS "NLOPT_INCLUDE_DIR: " ${NLOPT_INCLUDE_DIR})

# set(NLOPT_INCLUDE_DIR "C:\\Users\\sebas\\workspace\\3rdParty\\nlopt\\build\\install\\include")
set(NLOPT_STATIC_LIB ${CMAKE_CURRENT_SOURCE_DIR}/build/nlopt/nlopt.lib)

include_directories(
        ${GBS_INCLUDE_DIR}
        ${EIGEN3_INCLUDE_DIR}
        ${Boost_INCLUDE_DIR}
        ${NLOPT_INCLUDE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/inc
)
if(NOT MSVC)
add_compile_options(
        -Wdeprecated-declarations
)
endif()

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

pybind11_add_module(
        core MODULE  
        src/gbsBindBaseGeom.cpp
        src/gbsBindBasisFunctions.cpp
        src/gbsBindCurves.cpp
        src/gbsBindSurfaces.cpp
        src/gbsCoreBind.cpp
)

pybind11_add_module(
        interpolate MODULE  
        src/gbsbindinterp.cpp
        src/gbsbindapprox.cpp
        src/gbsInterpolateBind.cpp
)

pybind11_add_module(
        tools MODULE  
        src/gbsBindCurveTools.cpp
        src/gbsBindSurfaceTools.cpp
        src/gbsBindDiscretize.cpp
        src/gbsToolsBind.cpp
)

pybind11_add_module(
        analysis MODULE  
        src/gbsBindAnalysis.cpp
        src/gbsAnalysisBind.cpp
)

pybind11_add_module(
        transform MODULE  
        src/gbsBindTransform.cpp
        src/gbsTransformBind.cpp
)

pybind11_add_module(
        build MODULE  
        src/gbsbindbuildcurve.cpp
        src/gbsBindBuildSurfaces.cpp
        src/gbsBuildBind.cpp
)

# target_link_libraries(
#         interpolate PRIVATE 
#         core
# )

target_link_libraries(
        build PRIVATE 
        ${NLOPT_STATIC_LIB}
)

target_link_libraries(
        analysis PRIVATE 
        ${NLOPT_STATIC_LIB}
)

# Installer le module Python compilé
# scikit-build détectera cette instruction pour l'inclure dans la wheel
install(TARGETS
                core
                interpolate
                tools
                analysis
                transform
                build
        # LIBRARY DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/pygbs  # Sur certaines plateformes, on peut utiliser 'install' différemment
        LIBRARY DESTINATION ./pygbs  # Sur certaines plateformes, on peut utiliser 'install' différemment
)

file(GLOB_RECURSE PY_SRC_LIST "./pygbs/*.py")

message(STATUS "Python files" ${PY_SRC_LIST})

install(FILES 
        ${PY_SRC_LIST}
        DESTINATION 
        ./pygbs
)