cmake_minimum_required(VERSION 3.17 FATAL_ERROR)

project(step2)

set(MITK_SUPERBUILD_DIR "/home/jwu/mywork09/MITK_build")
set(QT_DIR "/home/jwu")

set(CMAKE_PREFIX_PATH
        "${MITK_SUPERBUILD_DIR}/MITK-build"
        "${MITK_SUPERBUILD_DIR}/ep/src/VTK/CMake/"
        "${QT_DIR}/Qt/5.15.11/gcc_64/lib/cmake/Qt5"
        )

find_package(MITK CONFIG REQUIRED)
find_package(OpenMP REQUIRED)

add_executable(${PROJECT_NAME} Step2.cpp)

target_link_libraries(${PROJECT_NAME} PUBLIC
        MitkCore
        MitkQtWidgetsExt
        )
