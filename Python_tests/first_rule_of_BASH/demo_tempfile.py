import tempfile
import os

# Automatically destroyed when the object is destroyed
# tempfile.mkstemp() is the equivalent except it only creates
# the file and returns the path, no object and no automatic deletion
t = tempfile.NamedTemporaryFile('w+', prefix='tmp_prefix', dir=os.getcwd(), suffix='hello')
print(f'Created file {t.name}')
fd, tmp_file_path = tempfile.mkstemp(prefix='mkstemp_', dir=os.getcwd())
print(f'Created file {tmp_file_path} which will not be deleted automatically')

# Automatically deleted temporary directory
# tempfile.mkdtemp() is the equivalent but it only creates the
# directory and returns the path, no automatic deletion
d = tempfile.TemporaryDirectory(prefix='dir', dir=os.getcwd(), suffix='_suffix')
print(f'Created directory {d.name}')
dd = tempfile.mkdtemp(prefix='mkdtemp_', dir=os.getcwd())
print(f'Created directory {dd} which will not be deleted automatically')

def create_scoped_tempfile():
    # Note, the first tempfile will be created and destroyed
    # since there is no variable referencing it.
    tempfile.NamedTemporaryFile('w+', prefix='unassigned_', dir=os.getcwd(), suffix='_tmp')
    # This second one will exist only for the duration of the function
    local_var = tempfile.NamedTemporaryFile('w+', prefix='assigned_local_', dir=os.getcwd(), suffix='_tmp')
    # This third one will continue to exist after the function if
    # we assign the return value to something
    ret = tempfile.NamedTemporaryFile('w+', prefix='returned_', dir=os.getcwd(), suffix='_tmp')
    input("press any key to let function end, the file will disappear >> ")
    return ret
create_scoped_tempfile()
input('press any key to call the function again but assign the return value >> ')
a = create_scoped_tempfile()

input('press any key to continue (will purpusefuly cause an exception, but our temporaries will still get deleted) >> ')
if os.path.isdir(dd):
    os.removedirs(dd)
if os.path.isfile(tmp_file_path):
    os.remove(tmp_file_path)


k = tempfile.TemporaryDirectory(dir='/no-exists')
