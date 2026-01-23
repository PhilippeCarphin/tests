program main


    logical :: undef
    write(*,*) "A Undef = ", undef

    if(undef) then
        write(*,*) "B 'if(undef)': undef=", undef
    endif
    if(.not. undef) then
        write(*,*) "C 'if(.not. undef)': undef=", undef
    endif

end program

