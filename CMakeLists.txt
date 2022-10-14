# IP Filter project
#
# CMake minimum version
set(PRJ_CMAKE_MIN_VERSION 3.2 CACHE INTERNAL "CMake version")
cmake_minimum_required(VERSION ${PRJ_CMAKE_MIN_VERSION})
# Project information
set(PRJ_NAME "ip_filter" CACHE INTERNAL "Project name")
set(PRJ_VERSION_MAJOR "0" CACHE INTERNAL "Minor version")
set(PRJ_VERSION_MINOR "0" CACHE INTERNAL "Major version")
set(PRJ_VERSION_PATCH "2" CACHE INTERNAL "Patch version")
set(PRJ_DESCRIPTION "Ip Filter project" CACHE INTERNAL "Project description")
set(PRJ_HOMEPAGE_URL "https://github.com/free0ON/otus_cpp_HW_02" CACHE INTERNAL "Project URL")
set(EMAIL_CONTACT "dmitrii.lozovoi@yandex.ru" CACHE INTERNAL "Email contact")

# Test options
#option(GOOGLE_TEST "Google test" ON)

project(${PRJ_NAME} VERSION ${PRJ_VERSION_MAJOR}.${PRJ_VERSION_MINOR}.${PRJ_VERSION_PATCH} DESCRIPTION "${PRJ_DESCRIPTION}" HOMEPAGE_URL "${PRJ_HOMEPAGE_URL}")
message("PROJECT_NAME: ${PROJECT_NAME} VERSION: ${PROJECT_VERSION}")
message("GOOGLE_TEST: ${GOOGLE_TEST}")
message("DESCRIPTION: ${PRJ_DESCRIPTION}")
message("HOMEPAGE_URL: ${PRJ_HOMEPAGE_URL}")
message("CMAKE_MINIMUM_REQUIRED_VERSION: ${CMAKE_MINIMUM_REQUIRED_VERSION}")

configure_file(src/version.h.in version.h)
add_library(ipaddress src/ipaddress.cpp)
add_library(version src/version.cpp)
add_executable(${PRJ_NAME} src/main.cpp)
add_executable(test_all test/test_all.cpp)
set_target_properties(${PRJ_NAME} ipaddress version test_all PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
        )
target_include_directories(${PRJ_NAME}
        PUBLIC
        "${CMAKE_BINARY_DIR}"
        src
        )

target_include_directories(version
        PUBLIC "${CMAKE_BINARY_DIR}"
        )
target_include_directories(test_all
        PRIVATE
        src
        )
target_link_libraries(${PRJ_NAME}
        PRIVATE
        ipaddress
        version
        )

target_link_libraries(test_all
        PRIVATE
        gtest
        gtest_main
        ipaddress
        version
        ${CMAKE_THREAD_LIBS_INIT}
)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
find_package(GTest REQUIRED)
enable_testing()
include(GoogleTest)
add_test(test_all test_all)
if (MSVC)
    target_compile_options(test_all PRIVATE  /W4)
else()
    target_compile_options(
            test_all PRIVATE
            -Wall -Wextra -pedantic -Werror)
endif(MSVC)
install(TARGETS ${PRJ_NAME} RUNTIME DESTINATION bin)
set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PRJ_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PRJ_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PRJ_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT "${EMAIL_CONTACT}")

include(CPack)

