# Attempt to replicate `set -e` behavior for sourcing

This test demonstrates an attempt to replicate the behavior of `set -e` for
a sourced file by doing

```
trap 'return 1' ERR
```

The problem is that when sourcing the file, this trap stays set to call 
`return 1` on `ERR` so if an executable script sources file, it now has `return 1`
as it's `ERR` signal handler.

```
# Executable script
set -e

source sourced_file.bash

ls noexist
```

The `ls noexist` will trigger the `ERR` signal handler which will say `return
can only be used in function or sourced script`.


