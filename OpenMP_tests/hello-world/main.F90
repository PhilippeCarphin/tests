module test

    contains
        subroutine my_main()

            use omp_lib

            integer :: i
            integer :: t
            integer :: sum
            integer :: nb_threads

            sum = 0

            !$omp parallel do
            do i=0,999
                t = omp_get_thread_num()
                write(*,*) t, "This is iteration", i
                if(i == 1) then
                    ! Needs to be done inside an OpenMP thing otherwise the function
                    ! always returns 1 (or 0 if OpenMP is not initialized)
                    nb_threads = omp_get_num_threads()
                endif
                sum = sum + i
            enddo

            write(*,*) "omp_get_num_threads -> ", nb_threads
            write(*,*) "sum = ", sum
        end subroutine
program OpenMP_Hello_World

    call my_main()

end program
