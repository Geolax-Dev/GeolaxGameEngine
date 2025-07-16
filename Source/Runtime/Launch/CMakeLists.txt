project(GGE.Runtime.Launch CXX)

file(GLOB_RECURSE SOURCES
    "**.cpp"
    "**.hpp"
)

add_executable(Startup WIN32 ${SOURCES})
target_link_libraries(Startup PRIVATE ${GGE_THIRD_PARTY_DEPENDENCIES})
