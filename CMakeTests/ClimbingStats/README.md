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
