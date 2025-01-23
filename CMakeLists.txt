cmake_minimum_required(VERSION 3.18)
project(pygbs LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)

# Trouver pybind11 (scikit-build va injecter les chemins si pybind11 est installé via pip/conda).
find_package(pybind11 REQUIRED)
find_package(Eigen3)
# find_package(gbs REQUIRED)
set(GBS_INCLUDE_DIR "/home/sebastien/micromamba/envs/dev/include/gbs")
include_directories(
        ${GBS_INCLUDE_DIR}
        ${EIGEN3_INCLUDE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/inc
)

pybind11_add_module(
        core
        src/gbsBindBaseGeom.cpp
        src/gbsBindBasisFunctions.cpp
        src/gbsBindCurves.cpp
        src/gbsBindSurfaces.cpp
        src/gbsCoreBind.cpp
)

pybind11_add_module(
        interpolate
        src/gbsbindinterp.cpp
        src/gbsbindapprox.cpp
        src/gbsInterpolateBind.cpp
)

pybind11_add_module(
        tools
        src/gbsBindCurveTools.cpp
        src/gbsBindSurfaceTools.cpp
        src/gbsBindDiscretize.cpp
        src/gbsToolsBind.cpp
)

pybind11_add_module(
        analysis
        src/gbsBindAnalysis.cpp
        src/gbsAnalysisBind.cpp
)

pybind11_add_module(
        transform
        src/gbsBindTransform.cpp
        src/gbsTransformBind.cpp
)

pybind11_add_module(
        build
        src/gbsbindbuildcurve.cpp
        src/gbsBindBuildSurfaces.cpp
)

# target_link_libraries(
#         build PRIVATE 
#         NLopt::nlopt 
# )


# Installer le module Python compilé
# scikit-build détectera cette instruction pour l'inclure dans la wheel
install(TARGETS
                core
                interpolate
                tools
                analysis
                transform
        LIBRARY DESTINATION .  # Sur certaines plateformes, on peut utiliser 'install' différemment
)
