program main
    integer :: argc, i, err, len
    character(len=:), allocatable :: arg
    character(len=1024), dimension(:), allocatable :: argv

    argc = command_argument_count()

    ! Option 1: more proper since we allocate the right lenght
    do i = 0,argc
        if(allocated(arg)) deallocate(arg)
        call get_command_argument(i,length=len)
        allocate(character(len=len) :: arg)
        call get_command_argument(i, arg, len, err)
    enddo

    ! Option 2: Easier but we need to use 'trim'
    allocate(argv(0:argc))
    do i = 0,argc
        call get_command_argument(i, argv(i), len, err)
    enddo

end program

