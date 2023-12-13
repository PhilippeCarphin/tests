
add_library(cpp STATIC lib.cpp lib.f90)
set_target_properties(cpp PROPERTIES PUBLIC_HEADER "lib.h;lib.hpp")

target_include_directories(cpp INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

install(TARGETS cpp)

