# Autotools tutorial

Following [Autotools Tutorial](https://www.lrde.epita.fr/~adl/autotools.html)
which is suggested by the the [introduction of the official documentation](https://www.gnu.org/software/automake/manual/html_node/Autotools-Introduction.html).

## Elements

- `configure`
  - Probes the system
  - Produces `config.h`
  - Produces `Makefile`(s)


## Tidbits

- If a `config.site` file exists at `${prefix}/share/config.site`, then using
  `./configure --prefix ${prefix}` will read this config and we can put options
  that would set variables on the `./configure` command.

- Configure supports out-of-tree builds!  We can do `mkdir build ; cd build ; ../configure`

## Sequence

Created
```
configure.ac
Makefile.am
srcx/Makefile.ac
```

Run command
```
autoreconf --install
```
This is equivalent (as can be seen by adding the `-v` flag) to
- `aclocal`: creates
  - `aclocal.m4`
  - `autom4te.cache`
  - `autoscan.log`
  - `configure.scan`
- `autoconf`: creates
  - `configure` (from `configure.ac`)
- `autoheader`: creates
  - `config.phil.h.in` (from `configure.ac`)
- `automake --add-missing --copy --no-force`: creates
  - `Makefile.in`s (from `Makefile.am`s and `configure.ac`)
  - `compile` (wrapper for compilers that do not understand `-c` and `-o`
  - `depcomp` a script
  - `install-sh`: Looks like it doesn what GNU install does

Note, the command `autoreconf` without the `--install` flag produces
```
configure.ac:7: error: required file './compile' not found
configure.ac:7:   'automake --add-missing' can install 'compile'
configure.ac:5: error: required file './install-sh' not found
configure.ac:5:   'automake --add-missing' can install 'install-sh'
configure.ac:5: error: required file './missing' not found
configure.ac:5:   'automake --add-missing' can install 'missing'
srcx/Makefile.am: error: required file './depcomp' not found
srcx/Makefile.am:   'automake --add-missing' can install 'depcomp'
autoreconf: automake failed with exit status: 1
```
that is because the option install:
```
$ man autoreconf
...
       -i, --install
                     copy missing auxiliary files
```

## configure.ac

- `AM_INIT_AUTOMAKE`:
  - `foreign` allows us to not follow certain conventions.  Without it, we would
    get messages like this about missing files:
    ```
    Makefile.am: error: required file './INSTALL' not found
    Makefile.am:   'automake --add-missing' can install 'INSTALL'
    Makefile.am: error: required file './NEWS' not found
    Makefile.am: error: required file './README' not found
    Makefile.am: error: required file './AUTHORS' not found
    Makefile.am: error: required file './ChangeLog' not found
    Makefile.am: error: required file './COPYING' not found
    Makefile.am:   'automake --add-missing' can install 'COPYING'
    ```

