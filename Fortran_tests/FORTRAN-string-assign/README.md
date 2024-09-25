# I don't understand character arrays in FORTRAN

## Initial context

(Code in this readme is heavily stripped, see the files for the real thing)

I have this C struct `TGrid` and functions that manipulate instances of that
struct:
```C
typedef struct TGrid {
   char     Id[14];                       ///< Grid identifier
   int      NI;                           ///< Size along X dimension
   // other stuff
} TGrid;
int Grid_print(TGrid* grid);
```

which I expose to Fortran.

```Fortran
module tgrid_mod
    TYPE, BIND(C) :: TGrid
        character(kind=C_CHAR)         :: Id(14)
        ! other stuff
    END TYPE
end module
```
and
```Fortran
module grid_mod
    use tgrid_mod
    interface
        integer(C_INT) FUNCTION grid_print(c_grid_ptr) BIND(C, name="Grid_print")
            use tgrid_mod
            TYPE(TGrid) :: c_grid_ptr
        END FUNCTION
    end interface
end module
```


I am restricted in how I declare the character array in FORTRAN.

I can declare a `TGrid` in FORTRAN and pass it to C:

```Fortran
program main
    use grid_mod
    TYPE(tgrid) :: the_grid
    the_grid%NI = 1337

    err = grid_print(the_grid)
end program
```
and when we run this, we see the `Grid->NI = 1337` received and printed by the
C function.

## The problem

How do I assign to `the_grid%Id`?

The only way I have found that works is just so sad:
```Fortran
    the_grid%Id(1:1) = "O"
    the_grid%Id(2:2) = "C"
    the_grid%Id(3:3) = "E"
    the_grid%Id(4:4) = "A"
    the_grid%Id(5:5) = "N"
    the_grid%Id(6:6) = c_null_char
```

Other attempts
```
the_grid%Id = "OCEAN"
```
resulted in `the_grid%Id` being just a bunch of `'O'`.

## Question

Is there a more elegant way to do this?

## Answer

The proper way is
```
the_grid%Id = transfer("OCEAN" // c_null_char, the_grid%Id)
```

But before receiving the suggestion to use `transfer`, it was suggested that I code up a function
which I did:
```Fortran
        integer function string_to_array(scalar, array)
            character(len=*), intent(IN) :: scalar                    ! One string of length N
            character(len=1), dimension(:), intent(OUT) :: array      ! N strings of length 1

            in_len = len_trim(scalar)
            out_shape = shape(array)

            if(out_shape(1) < in_len+1) then
                string_to_array = 1
                return
            endif

            do i=1,in_len
                array(i) = scalar(i:i)
            enddo

            array(in_len+1) = c_null_char

            string_to_array = 0
            return
        end function
```
which was fun because it forced me to get the right declaration for the argument that would receive the hardcoded string `"OCEAN"`.

