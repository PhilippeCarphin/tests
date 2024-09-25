program main
    ! This test demonstrates the use of the `transfer` builtin function
    ! to assign a literal to a C-string.  There are many ways to declare
    ! a thing that holds N characters but not all of them are allowed in
    ! bind(C) types.
    use, intrinsic :: iso_c_binding

    type, bind(C) :: t
        ! Needs to be like this to be bind(C)
        character(kind=C_CHAR) :: nomvar(5)

        ! With this declaration, Attempt 1 would work but this declaration
        ! is not strictly allowed for bind(C) types.
#ifdef __INTEL_COMPILER
        character(kind=C_CHAR, len=5) :: nomvar_len
#endif
        ! Intel produces this warning:
        !       (14): warning #8753: A CHARACTER component of an interoperable
        !       derived type must have length 1.   [NOMVAR_LEN]
        ! gfortran produces this error:
        !       Error: Component ‘nomvar_len’ of BIND(C) type at (1) must have
        !              length one

    end type

    type(t) :: my_t

    ! Attempt 1 failed result: Makes each element equal to 'A', so we get
    ! "AAAAA"
    write(*,'(a)') "Attempt 1: Assigning the literal directly:"
    my_t%nomvar = "ASDF" // c_null_char
    write(*,*) my_t%nomvar

    ! Attempt 2 successful result, shameful code
    write(*,'(a)') "Attempt 2: Assigning characters individually:"
    my_t%nomvar(1) = "A"
    my_t%nomvar(2) = "S"
    my_t%nomvar(3) = "D"
    my_t%nomvar(4) = "F"
    my_t%nomvar(5) = c_null_char
    write(*,*) my_t%nomvar

#ifdef __INTEL_COMPILER
    ! With this the assign works but the declaration
    ! is not ok for a C-interoperable type

    write(*,'(a)') "Attempt x: Using dissalowed string type with Intel compiler:"
    my_t%nomvar_len = "ASDF" // c_null_char
    write(*,*) my_t%nomvar_len
#endif

    ! This is the proper way. `transfer` is a standard function
    ! The second argument is called MOLD and it says what shape
    ! the return value needs to have.  So `X = transfer(..., X)`
    ! is a common way to use `transfer`.
    write(*,'(a)') "Attempt 3: The proper way using transfer:"
    my_t%nomvar = transfer("ASDF" // c_null_char, my_t%nomvar)
    write(*,*) my_t%nomvar

end program
