program main
    use, intrinsic :: iso_fortran_env, only: error_unit
    implicit none

    type :: person_type
        integer           :: id
        character(len=32) :: name
        integer           :: age
    end type person_type

    type :: phil_t
        integer           :: int
        character(len=32) :: color
        logical           :: bool
    end type phil_t

    integer           :: x, y, ierr
    real              :: r(2)
    type(person_type) :: person
    type(phil_t)      :: foo

    ! Set initial values.
    person = person_type(-1, 'Jane Doe', 0)
    x = 0; y = 0
    r = [ 0.0, 0.0 ]
    foo%int=42

    ! Read from file.
    call read_namelist('namelist.nml', person, foo, x, y, r, ierr)
    if(ierr /= 0) then
        stop 8
    endif

    ! Output some values.
    print '("PERSON ID:   ", i0)', person%id
    print '("PERSON NAME: ", a)',  person%name
    print '("PERSON AGE:  ", i0)', person%age
    print '("FOO INT:   " i0)', foo%int
    print '("FOO COLOR: " a)', foo%color
    print '("FOO BOOL:  " l)', foo%bool
contains
    subroutine read_namelist(file_path, person, foo, x, y, r, status)
        !! Reads Namelist from given file.
        character(len=*),  intent(in)    :: file_path
        type(person_type), intent(inout) :: person
        type(phil_t),      intent(inout) :: foo
        integer,           intent(inout) :: x, y
        real,              intent(inout) :: r(2)
        integer,           intent(out)   :: status
        integer                          :: fd, ierr
        logical                          :: exists

        ! Namelist definition.
        namelist /PHIL/ foo
        namelist /EXAMPLE/ x, y, r, person

        exists = .true.
        ! Check whether file exists.
        write (error_unit, '("Checking if file ", a, " exists")') file_path
        inquire (file=file_path, exist=exists, iostat=ierr)
        write (error_unit, '("Checking if file ", a, " exists")') file_path

        if (.not. exists) then
            write (error_unit, '("Error: input file ", a, " does not exist")') file_path
            status = 8
            return
        else
            write(error_unit, *) "File exists"
        end if

        ! Open and read Namelist file.
        open (action='read', file=file_path, iostat=ierr, newunit=fd)
        if(ierr /= 0) then
            write (error_unit, '("Error: opening file ", a)') file_path
        endif
        read (nml=EXAMPLE, iostat=ierr, unit=fd)
        if (ierr /= 0) then
            write (error_unit, '("Error: invalid Namelist format")')
            status = 8
            return
        endif

        read (nml=PHIL, iostat=ierr, unit=fd)
        if (ierr /= 0) then
            write (error_unit, '("Error: invalid Namelist format")')
            status = 8
            return
        endif

        close (fd)
        status = 0
    end subroutine read_namelist
end program main
