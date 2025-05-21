cmake_minimum_required(VERSION 3.10)

# Set the project name and type
project(DataStructures VERSION 1.0.0 LANGUAGES CXX)

# Create the library target
add_library(DataStructures STATIC
    # src/node.cpp
    # src/skip_list.cpp
    src/entry.cpp
)

# Specify the include directories for consumers of the library
target_include_directories(DataStructures PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/inc>
    $<INSTALL_INTERFACE:include>
)

# Set C++ standard
target_compile_features(DataStructures PUBLIC cxx_std_20)

# Install the target
install(TARGETS DataStructures
    EXPORT DataStructuresTargets
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
    INCLUDES DESTINATION include
)

install(DIRECTORY inc/ DESTINATION include)

# Export target for find_package()
install(EXPORT DataStructuresTargets
    FILE DataStructuresTargets.cmake
    NAMESPACE data_struct::
    DESTINATION lib/cmake/DataStructures
)

# Package configuration file
include(CMakePackageConfigHelpers)

write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/DataStructuresConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/DataStructuresConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/DataStructuresConfig.cmake"
    INSTALL_DESTINATION lib/cmake/DataStructures
)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/DataStructuresConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/DataStructuresConfigVersion.cmake"
    DESTINATION lib/cmake/DataStructures
)

add_subdirectory(example)