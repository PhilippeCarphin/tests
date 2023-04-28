cmake_minimum_required(VERSION 3.20)

project(info C)

if(DO_MPI_STATIC_THING)
    # Read in FindMPI.cmake where it affects the properties that are set on
    # MPI::MPI_C and MPI::MPI_Fortran
    set(MPI_Fortran_COMPILER_FLAGS -static_mpi)
    set(MPI_C_COMPILER_FLAGS -static_mpi)
endif()
find_package(MPI REQUIRED COMPONENTS)

include(CMakePrintHelpers)

cmake_print_properties(TARGETS MPI::MPI_C
    PROPERTIES
        INTERFACE_COMPILE_OPTIONS
        INTERFACE_LINK_OPTIONS
        INTERFACE_LINK_LIBRARIES
        IMPORTED_LOCATION
        IMPORTED_LOCATION_DEBUG
        IMPORTED_LOCATION_RELWITHDEBINFO
        IMPORTED_LOCATION_MINSIZEREL
        IMPORTED_LOCATION_RELEASE
)
