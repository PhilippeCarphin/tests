cmake_minimum_required(VERSION 3.20)

project(env_for_execute_process C Fortran)

set(ENV{X} "VALUE OF X")

# 1. FindGDAL.cmake utilise
#
#    find_path(var file
#      HINTS
#        ENV GDAL_DIR
#        ENV GDAL_ROOT
#      ...
#    )
#
#    donc seule les variables d'environnement ont un effet (-DGDAL_ROOT change rien)
#
# 2. On peut trouver GDAL_ROOT avec un execute_process.  Ça n'affecte pas l'env
#    donc ça n'affecte pas le find.
#
# 3. On peut setter la variable d'en


# execute_process(COMMAND bash -c "echo X=$X" OUTPUT_VARIABLE out)
# message(STATUS "out=${out}")
# 

execute_process(COMMAND bash -c "cd $(dirname $(which gdal-config))/.. && pwd" OUTPUT_VARIABLE GDAL_ROOT OUTPUT_STRIP_TRAILING_WHITESPACE)
message(STATUS "GDAL_ROOT=${GDAL_ROOT}")
# set(ENV{GDAL_ROOT} ${GDAL_ROOT}

execute_process(COMMAND bash -c "cd $(dirname $(which gdal-config))/.. && pwd" OUTPUT_VARIABLE x OUTPUT_STRIP_TRAILING_WHITESPACE)
# set(ENV{GDAL_ROOT} ${x})

find_package(GDAL 2.0.0 REQUIRED)
