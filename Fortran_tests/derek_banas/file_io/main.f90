program fortrantut
    implicit none

    character (len=100) :: str = "I'm a string"
    character (len=100) :: str2

    integer err_status
    character(256) :: err_iomsg

    ! Open a file, Fails if the file already exists because of status new
    open(10, file='data.dat', status='new', iostat=err_status, iomsg=err_iomsg)
    if(err_status /= 0) then
        write (*,*) 'Error ', trim(err_iomsg)
        stop
    end if

    ! Write to the file
    write (10, '(A)') str

    ! Normal close like in C, see further for use with status='delete'
    ! to close with deletion.
    close(10)

    ! close(10, status='delete') if the file 'data.dat' was not there because
    ! we closed with status='delete', then the open call with the status='old'
    ! will fail because 'old' means the file is expected to exist
    open(11, file='data.dat', status='old', iostat=err_status, iomsg=err_iomsg)
    if(err_status /= 0) then
        write (*,*) 'Error ', trim(err_iomsg)
        stop
    end if

    ! Read and print the contents of the file, str2 should be "I'm a string"
    read (11, '(A)') str2
    write (*, '(A)') trim(str2)

    ! Close with deletion so that the open(..., status='new') will work
    ! on future runs.
    close(11, status="delete")

end program fortrantut
