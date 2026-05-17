# CMakeLists.txt for CEngine
# (C) 2026 Daniel McGuire - MIT License

cmake_minimum_required(VERSION 3.14)
project(CalcEngine CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(Ratpack STATIC
    Ratpack/basex.cpp
    Ratpack/conv.cpp
    Ratpack/exp.cpp
    Ratpack/fact.cpp
    Ratpack/itrans.cpp
    Ratpack/itransh.cpp
    Ratpack/logic.cpp
    Ratpack/num.cpp
    Ratpack/rat.cpp
    Ratpack/support.cpp
    Ratpack/trans.cpp
    Ratpack/transh.cpp
)
target_include_directories(Ratpack PUBLIC .)

add_library(CalcEngine STATIC
    CEngine/CalcInput.cpp
    CEngine/CalcUtils.cpp
    CEngine/History.cpp
    CEngine/Number.cpp
    CEngine/Rational.cpp
    CEngine/RationalMath.cpp
    CEngine/calc.cpp
    CEngine/scicomm.cpp
    CEngine/scidisp.cpp
    CEngine/scifunc.cpp
    CEngine/scioper.cpp
    CEngine/sciset.cpp
    ExpressionCommand.cpp
)
target_include_directories(CalcEngine PUBLIC .)
target_link_libraries(CalcEngine PUBLIC Ratpack)

option(CALC_ENGINE_BUILD_EXAMPLE "Build the example program" OFF)

if(CALC_ENGINE_BUILD_EXAMPLE)
    add_executable(calc_example example/main.cpp)
    target_link_libraries(calc_example PRIVATE CalcEngine)
endif()
