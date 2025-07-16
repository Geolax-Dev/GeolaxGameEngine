cmake_minimum_required(VERSION 3.30 FATAL_ERROR)
project(GeolaxGameEngine)

# Minimals setup

include(cmake/UtilityFunctions.cmake)

set(GGE_SOURCE_DIR "${CMAKE_SOURCE_DIR}")
gge_log("Setting up source dir: ${CMAKE_SOURCE_DIR}")

set(GGE_THIRD_PARTY_DIR "${GGE_SOURCE_DIR}/Runtime/ThirdParty")
gge_log("Setting up third party root: ${GGE_THIRD_PARTY_DIR}")

# Standard setup options

include(cmake/StandardSetup.cmake)

# Setting up third party libraries

gge_log("Setting up third parties...")
setup_third_party_common("glfw" "include")
setup_third_party_common("entt" "src")
setup_third_party_common("Vulkan-Headers" "include")
setup_third_party_common("openssl-cmake" "")
setup_third_party_header_only("imgui" "")
setup_third_party_header_only("imgui-node-editor" "")
setup_third_party_complex("JoltPhysics" "Build")
gge_log("Done setting up third parties!")

set(GGE_THIRD_PARTY_DEPENDENCIES
    glfw
    EnTT
    Jolt
    crypto
)

# Setting up our codebase

gge_log("Setting up runtime...")

setup_core_library("Runtime-Core" "Runtime/Core")
setup_core_executable("Startup" "Runtime/Launch")
