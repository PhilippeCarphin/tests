program preproc
    use, intrinsic :: iso_fortran_env
    implicit none
    write(output_unit,*) "With preprocessor"
#include "include_file.hf"
    stop 0
end program
