program main

    use, intrinsic :: iso_fortran_env
    implicit none

    integer, PARAMETER :: cplatm_n_fldou=38
    integer :: iout
    integer :: ivar

    character(len=3), dimension(cplatm_n_fldou) :: cplatm_cvou_S
    character(len=1), dimension(cplatm_n_fldou) :: cplatm_cvot_S

    data cplatm_cvou_S /'MCP','ALO','ALI','T4O','T4I',  &
                        'SHO','SHI','LHO','LHI',        &
                        'TXO','TYO','TXI','TYI',        &
                        'ZTO','ZQO','ZUO','ZVO',        &
                        'ZTI','ZQI','ZUI','ZVI',        &
                        'GLI','I8I','SDI','TMO',        &
                        'UUO','VVO','I7I','UUI','VVI',  &
                        'QSO','QSI','ILO','ILI',        &
                        'ZMO','ZMI','ZHO','ZHI'      /
    data cplatm_cvot_S /'S'  ,'S'  ,'S'  ,'S',  'S'  ,  &
                        'S'  ,'S'  ,'S'  ,'S'  ,        &
                        'U'  ,'V'  ,'U'  ,'V'  ,        &
                        'S'  ,'S'  ,'U'  ,'V'  ,        &
                        'S'  ,'S'  ,'U'  ,'V'  ,        &
                        'S'  ,'S'  ,'S'  ,'S'  ,        &
                        'U'  ,'V'  ,'S'  ,'U'  ,'V',    &
                        'S'  ,'S'  ,'S'  ,'S'  ,        &
                        'S'  ,'S'  ,'S'  ,'S'        /
    character(len=:), allocatable :: composed_string

    call compose_iris_field_name_string(cplatm_cvou_S, cplatm_cvot_S, composed_string)
    write(error_unit,'("composed_string=",a)') composed_string

contains
    subroutine compose_iris_field_name_string(field_names, field_types, composed_string)
        use, intrinsic :: iso_c_binding
        character(len=:), allocatable, intent(out) :: composed_string
        character(len=*), dimension(:), intent(in) :: field_names
        character(len=*), dimension(:), intent(in) :: field_types

        integer :: ivar

        allocate(character(len=(size(field_names,1) * (1+len(field_names(:))))) :: composed_string)
        do ivar = 1, size(cplatm_cvou_S,1)
        if(ivar .ne. 1) then
            if(cplatm_cvot_S(ivar-1) == 'S' .or. cplatm_cvot_S(ivar-1) == 'V') then
                composed_string = composed_string // ','
            elseif (cplatm_cvot_S(ivar-1) == 'U') then
                if (cplatm_cvot_S(ivar) .ne. 'V') then
                    write(error_unit,*) "Incoherent variable types"
                    stop 1
                endif
                composed_string = composed_string // '/'
            endif
        endif
        composed_string = composed_string // cplatm_cvou_S(ivar)
        enddo
        composed_string = composed_string // c_null_char
    end subroutine
end program
