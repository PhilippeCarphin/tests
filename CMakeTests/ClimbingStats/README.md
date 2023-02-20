# Automatic generation of package files

This project demonstrates how CMake package configuration files can be generated
for exporting the targets of a project.

The install directory will have a file `lib/cmake/climbingstats-3.14.15` which 
will contain a file `climbingstats-config.cmake`:
```cmake
# climbingstats-config.cmake
include(CMakeFindDependencyMacro)
find_dependency(LibXml2 REQUIRED)
include(${CMAKE_CURRENT_LIST_DIR}/ClimbingStatsTargets.cmake)
```
We don't need to put anything else in the file, the rest is generated 
automatically from the properties of our targets.

# How to do it

This project has a couple things to make it representative of other projects.

- Two targets `climber` and `climbingstats` with one target `climbingstats` that
  depends on the other target `climber`.
- The targets have some public and private compile options and definitions as
  well as link libraries.
- `find_package(LibXml2)`.  It represents a transitive dependency of our project.
  Because we have `target_link_libraries(climber PUBLIC LibXml2::LibXml2)`,
  client projects will need to link with it as well and our config file will
  need to account for that.
- `find_package(OpenSSL)`.  This is a non-transitive dependency of our project
  We use it to build the executable `climbingtool` there fore client projects
  dont care about it.

## Adding EXPORT to install commands

We add the argument `EXPORT <export-name>` to the install commands that we
already have for our targets.  This defines an "export" thing.

```cmake
# src/climber/CMakeLists.txt
install(
    TARGETS climber
    EXPORT ClimbingStatsTargets
    # ...
)
```

```cmake
# src/climber/CMakeLists.txt
install(
    TARGETS climbingstats
    EXPORT ClimbingStatsTargets
    # ...
)
```

No files get created from this.

## Add an install command for the "export" thing

```cmake
# CMakeLists.txt
install(EXPORT ClimbingStatsTargets
    FILE ClimbingStatsTargets.cmake
    DESTINATION ${CONFIG_INSTALL_DIR}
    NAMESPACE climbingstats::
)
```

This creates a set of files from the "export" thing ClimbingStatsTargets
which will create imported targets with the same usage requirements as the
targets of our project.

# Result

For convenience, the config files generated after `make install` are tracked
with this repo at [./install-dir/lib/cmake/climbingstats-3.14.15](./install-dir/lib/cmake/climbingstats-3.14.15)

We build and install the project and look at what we find in the `lib/cmake/climbingstats-3.14.15`
subdirectory of our install location.

- `climbingstats-config.cmake`
- `ClimbingStatsTargets.cmake`
- `ClimbingStastTargets-<X>.cmake`

where the `<X>` is `${CMAKE_BUILD_TYPE}` in lowercase form.

Together, these files define "imported targets".  The PUBLIC compile options,
definitions, include directories, and link options etc. are set as `INTERFACE_*`,
properties of these targets.

Aside from the file we wrote ourselves, there are two files that were generated

- `ClimbingStatsTargets.cmake`:
  - Protection against double inclusion
  - Created imported targets
  - Set all their usage requirements (`INTERFACE_*` properties)
  - include all `ClimbingStatsTargets-*` files
  - Make sure all the necessary files exist

- `ClimbingStatsTargets-<X>`
  - Set the `IMPORTED_LOCATION_<X>` properties of the targets

The only thing that we need to reproduce by hand is the `find_package(LibXml2 REQUIRED)`
that becomes `find_dependency(LibXml2 REQUIRED)` in our `climbingstats-config.cmake.in`
file.

# Other things to note

- I used generator expressions for the public compile definitions of the target
  `climbingstats`.  The generator expressions are transferred to the
  `INTERFACE_COMPILE_DEFINITIONS` of the imported targets in `ClimbingStatsTargets.cmake`.
- I used `-W` flags as the example of private compile options.  This is a well
  chosen example since they are not usage requirements of our targets and should
  not be forced on client projects.
- `find_dependency()` is used instead of `find_package()`.  I don't remember
  where I read this but this is not optionnal.  I read somewhere that `find_package()`
  should absolutely not be used in package config files.  Anyway, `find_dependency()`
  is a wrapper for `find_package()`
- We don't need to use `configure_package_config_file()` since the stuff that
  `@PACKAGE_INIT@` gives us is is replaced by things in the generated files.

# Usage example

See the companion project `../UseClimbingStats` for an example project that
uses this project.

# References

## For `install(TARGETS ... EXPORT`)

https://cmake.org/cmake/help/latest/command/install.html#targets

```
install(TARGETS targets... [EXPORT <export-name>]
        [RUNTIME_DEPENDENCIES args...|RUNTIME_DEPENDENCY_SET <set-name>]
        [[ARCHIVE|LIBRARY|RUNTIME|OBJECTS|FRAMEWORK|BUNDLE|
          PRIVATE_HEADER|PUBLIC_HEADER|RESOURCE|FILE_SET <set-name>|CXX_MODULES_BMI]
         [DESTINATION <dir>]
         [PERMISSIONS permissions...]
         [CONFIGURATIONS [Debug|Release|...]]
         [COMPONENT <component>]
         [NAMELINK_COMPONENT <component>]
         [OPTIONAL] [EXCLUDE_FROM_ALL]
         [NAMELINK_ONLY|NAMELINK_SKIP]
        ] [...]
        [INCLUDES DESTINATION [<dir> ...]]
        )
...
EXPORT
    This option associates the installed target files with an export called
    <export-name>. It must appear before any target options. To actually install
    the export file itself, call install(EXPORT), documented below. See
    documentation of the EXPORT_NAME target property to change the name of the
    exported target.

    If EXPORT is used and the targets include PUBLIC or INTERFACE file sets, all
    of them must be specified with FILE_SET arguments. All PUBLIC or INTERFACE
    file sets associated with a target are included in the export.
INCLUDES DESTINATION
    This option specifies a list of directories which will be added to the
    INTERFACE_INCLUDE_DIRECTORIES target property of the <targets> when exported
    by the install(EXPORT) command. If a relative path is specified, it is
    treated as relative to the $<INSTALL_PREFIX>.
```

## For `install(EXPORT`

https://cmake.org/cmake/help/latest/command/install.html#installing-exports

```
install(EXPORT <export-name> DESTINATION <dir>
        [NAMESPACE <namespace>] [FILE <name>.cmake]
        [PERMISSIONS permissions...]
        [CONFIGURATIONS [Debug|Release|...]
        [CXX_MODULES_DIRECTORY <directory>]
        [EXPORT_LINK_INTERFACE_LIBRARIES]
        [COMPONENT <component>]
        [EXCLUDE_FROM_ALL])
install(EXPORT_ANDROID_MK <export-name> DESTINATION <dir> [...])

The EXPORT form generates and installs a CMake file containing code to import
targets from the installation tree into another project. Target installations
are associated with the export <export-name> using the EXPORT option of the
install(TARGETS) signature documented above. The NAMESPACE option will prepend
<namespace> to the target names as they are written to the import file.
```

## Full explained example
https://cmake.org/cmake/help/latest/guide/importing-exporting/index.html#exporting-targets

> While IMPORTED targets on their own are useful, they still require that the project that imports them knows the locations of the target files on disk. The real power of IMPORTED targets is when the project providing the target files also provides a CMake file to help import them. A project can be setup to produce the necessary information so that it can easily be used by other CMake projects be it from a build directory, a local install or when packaged.
>
> In the remaining sections, we will walk through a set of example projects step-by-step. The first project will create and install a library and corresponding CMake configuration and package files. The second project will use the generated package.

## Another explained example

https://cmake.org/cmake/help/latest/manual/cmake-packages.7.html#creating-packages

## Possible locations of config files

https://cmake.org/cmake/help/latest/command/find_package.html#config-mode-search-procedure



