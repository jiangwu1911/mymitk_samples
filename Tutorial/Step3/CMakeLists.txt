cmake_minimum_required(VERSION 3.17 FATAL_ERROR)

project(step3)

set(MITK_SUPERBUILD_DIR "/home/jwu/mywork08/MITK_2024")

set(CMAKE_PREFIX_PATH
    "${MITK_SUPERBUILD_DIR}/MITK-build"
)

find_package(MITK CONFIG REQUIRED)
find_package(OpenMP REQUIRED)

add_executable(${PROJECT_NAME} Step3.cpp)

target_link_libraries(${PROJECT_NAME} PUBLIC
    MitkCore
    MitkQtWidgets
)
