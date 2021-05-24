program hello
    real*8, parameter :: pi = 3.14159
    print *, "Hello World!"
    write(6,10) pi 
10   format (f12.6)
end program