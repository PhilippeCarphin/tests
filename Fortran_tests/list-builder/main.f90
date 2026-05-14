program hello
    use, intrinsic :: iso_fortran_env
    implicit none
    integer, dimension(:), allocatable :: component_ids
    integer :: GEM_comp_id = 3
    integer :: INs_comp_id = 40
    integer :: OUTs_comp_id = 8

    component_ids = [GEM_comp_id]
    if(INs_comp_id >= 0) then
        component_ids = [component_ids, [INs_comp_id]]
    endif
    if(OUTs_comp_id >= 0) then
        component_ids = [component_ids, [OUTs_comp_id]]
    endif

    write(error_unit,*) "Component IDs: ", component_ids
    write(error_unit,"('shape: ', i1, ', rank:', i1, ', size:', i1)") shape(component_ids), rank(component_ids), size(component_ids)

    if(size(component_ids) == 1) then
        write(error_unit, "(a)") "comm = App_MPMD_SelfComm()"
    else
        write(error_unit, "(a)") "comm = App_MPMD_GetSharedComm(component_ids, .false.)"
    endif

end program
