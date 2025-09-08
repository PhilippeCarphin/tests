PROGRAM main
    use datetime_mod

    integer(C_LONG) :: datetime
    integer(C_INT) :: err

    datetime =  11512092260 ! 2021-11-21 00:00
    err = f_print_datetime(datetime)

END PROGRAM
