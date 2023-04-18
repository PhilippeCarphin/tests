#----------------------------------------------------------------
# Generated CMake target import file for configuration "RelWithDebInfo".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "climbingstats::climber" for configuration "RelWithDebInfo"
set_property(TARGET climbingstats::climber APPEND PROPERTY IMPORTED_CONFIGURATIONS RELWITHDEBINFO)
set_target_properties(climbingstats::climber PROPERTIES
  IMPORTED_LOCATION_RELWITHDEBINFO "${_IMPORT_PREFIX}/lib/libclimber.so"
  IMPORTED_SONAME_RELWITHDEBINFO "libclimber.so"
  )

list(APPEND _cmake_import_check_targets climbingstats::climber )
list(APPEND _cmake_import_check_files_for_climbingstats::climber "${_IMPORT_PREFIX}/lib/libclimber.so" )

# Import target "climbingstats::climbingstats" for configuration "RelWithDebInfo"
set_property(TARGET climbingstats::climbingstats APPEND PROPERTY IMPORTED_CONFIGURATIONS RELWITHDEBINFO)
set_target_properties(climbingstats::climbingstats PROPERTIES
  IMPORTED_LOCATION_RELWITHDEBINFO "${_IMPORT_PREFIX}/lib/libclimbingstats.so"
  IMPORTED_SONAME_RELWITHDEBINFO "libclimbingstats.so"
  )

list(APPEND _cmake_import_check_targets climbingstats::climbingstats )
list(APPEND _cmake_import_check_files_for_climbingstats::climbingstats "${_IMPORT_PREFIX}/lib/libclimbingstats.so" )

# Import target "climbingstats::climbingtool" for configuration "RelWithDebInfo"
set_property(TARGET climbingstats::climbingtool APPEND PROPERTY IMPORTED_CONFIGURATIONS RELWITHDEBINFO)
set_target_properties(climbingstats::climbingtool PROPERTIES
  IMPORTED_LOCATION_RELWITHDEBINFO "${_IMPORT_PREFIX}/bin/climbingtool"
  )

list(APPEND _cmake_import_check_targets climbingstats::climbingtool )
list(APPEND _cmake_import_check_files_for_climbingstats::climbingtool "${_IMPORT_PREFIX}/bin/climbingtool" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
