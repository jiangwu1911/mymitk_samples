cmake_minimum_required(VERSION 3.17 FATAL_ERROR)

project(step6)

set(CMAKE_AUTOMOC ON)

set(MITK_SUPERBUILD_DIR "/home/jwu/mywork09/MITK_build")
set(QT_DIR "/home/jwu")

set(CMAKE_PREFIX_PATH
        "${MITK_SUPERBUILD_DIR}/MITK-build"
        "${MITK_SUPERBUILD_DIR}/ep/src/VTK/CMake/"
        "${QT_DIR}/Qt/5.15.11/gcc_64/lib/cmake/Qt5"
        )

find_package(MITK CONFIG REQUIRED)
find_package(OpenMP REQUIRED)
find_package(ITK REQUIRED)
find_package(Qt5 5.12 COMPONENTS Widgets Charts Svg REQUIRED)

add_executable(${PROJECT_NAME} 
        Step6.cpp  
        Step6main.cpp
        Step6RegionGrowing1.cpp  
        Step6RegionGrowing2.cpp  
        Step6RegionGrowing3.cpp
)

target_link_libraries(${PROJECT_NAME} PUBLIC
        MitkCore
        MitkQtWidgetsExt
        Qt5::Widgets
        ${ITK_LIBRARIES}
        )
