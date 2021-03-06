cmake_minimum_required(VERSION 3.2)

set(PROGRAM_NAME "matrix")

if (DEFINED ENV{GITHUB_RUN_NUMBER})
    project(${PROGRAM_NAME} VERSION 0.0.$ENV{GITHUB_RUN_NUMBER})
else()
    project(${PROGRAM_NAME} VERSION 0.0.111)
endif() 

find_package(Boost COMPONENTS unit_test_framework REQUIRED)

configure_file(version.h.in src/version.h)

add_executable(${PROGRAM_NAME} src/main.cpp)
add_library(${PROGRAM_NAME}_lib src/lib.cpp)
add_executable(test_version src/test_version.cpp)

set_target_properties(${PROGRAM_NAME} ${PROGRAM_NAME}_lib test_version PROPERTIES
    CXX_STANDARD 17
    #CXX_STANDARD 14
    #CXX_STANDARD 11
    CXX_STANDARD_REQUIRED ON
)
target_include_directories(${PROGRAM_NAME}_lib
    PRIVATE "${CMAKE_BINARY_DIR}"
 )
set_target_properties(test_version PROPERTIES
    COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
    INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
)

target_link_libraries(${PROGRAM_NAME} PRIVATE
    ${PROGRAM_NAME}_lib
 )
target_link_libraries(test_version
    ${Boost_LIBRARIES}
    ${PROGRAM_NAME}_lib
)

if (MSVC)
    target_compile_options(${PROGRAM_NAME} PRIVATE
        /W4
    )
    target_compile_options(${PROGRAM_NAME}_lib PRIVATE
        /W4
    )
    target_compile_options(test_version PRIVATE
        /W4
    )
else ()
    target_compile_options(${PROGRAM_NAME} PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(${PROGRAM_NAME}_lib PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(test_version PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()



install(TARGETS ${PROGRAM_NAME} RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT example@example.com)

include(CPack)

enable_testing()

add_test(test_version test_version)
