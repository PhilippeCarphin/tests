PROJECT(calling_convention CXX C)


add_executable(main main.cpp)
target_compile_options(main PUBLIC -O3)
add_library(rmn SHARED rmn.c)
target_compile_options(rmn PRIVATE -std=c99)
target_compile_options(rmn PUBLIC -O3)

target_link_libraries(main PRIVATE rmn)
