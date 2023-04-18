
include(CMakePrintHelpers)

cmake_print_variables(${CMAKE_FIND_PACKAGE_NAME}_FIND_COMPONENTS)

if(${CMAKE_FIND_PACKAGE_NAME}_FIND_COMPONENTS)
    if("shared" IN_LIST ${CMAKE_FIND_PACKAGE_NAME}_FIND_COMPONENTS)
        if("ompi" IN_LIST ${CMAKE_FIND_PACKAGE_NAME}_FIND_COMPONENTS)
            message(STATUS "include(\${CMAKE_CURRENT_LIST_DIR}/rmn-shared-ompi-target.cmake)")
            # set component found thing
        else()
            message(STATUS "include(\${CMAKE_CURRENT_LIST_DIR}/rmn-shared-target.cmake)")
            # set component found thing
        endif()
    else()
        if("ompi" IN_LIST ${CMAKE_FIND_PACKAGE_NAME}_FIND_COMPONENTS)
            message(STATUS "include(\${CMAKE_CURRENT_LIST_DIR}/rmn-shared-ompi-target.cmake)")
            # set component found thing
        else()
            message(STATUS "include(\${CMAKE_CURRENT_LIST_DIR}/rmn-shared-target.cmake)")
            # set component found thing
        endif()
    endif()
else()
    foreach(target IN ITEMS rmn rmn-shared rmn-ompi rmn-shared-ompi)
        set(file ${CMAKE_CURRENT_LIST_DIR}/${target}-target.cmake)
        if(EXISTS ${file})
            message(STATUS "include(\${CMAKE_CURRENT_LIST_DIR}/${target}-target.cmake)")
        else()
            message(STATUS "PISS BUCKET ${file}")
        endif()
    endforeach()
endif()



include(${CMAKE_CURRENT_LIST_DIR}/shades-target.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/leatherjacket-target.cmake)
