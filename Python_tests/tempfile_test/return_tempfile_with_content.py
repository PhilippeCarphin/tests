import tempfile
import os

def create_tempfile(contents):
    # default mode='w+b', I don't want 'b'
    tf = tempfile.NamedTemporaryFile(mode='w')

    if isinstance(contents, dict):
        for key, value in contents.items():
            tf.write(f'{key}={value}')
    elif isinstance(contents, list):
        tf.write(' '.join(contents) + '\n')
    else:
        tf.write(contents)

    # Running tf.close() would delete the file
    # Without tf.file.close() the contents will not necessarily get
    # flushed to the file.
    tf.file.close()

    # Return tf.name separately to check the destruction of the file
    # Normally, your would just return tf
    return tf.name, tf

def test_encoding():
    (fdunit,filename) = tempfile.mkstemp()
    fd = os.fdopen(fdunit,"w")
    fd.write("Hello World")
    fd.close()
    return filename

def main():
    filename, handle = create_tempfile({"hello": "world"})


    with open(handle.name, 'r') as f:
        print(f.read())
    # Then destructor of the NamedTemporaryFile object.  What follows is an
    # implementation detail, but uncommenting the following line to none
    # should cause the file to be deleted before the check.  By assigning None
    # to the variable handle, we decrease the refcount of the NamedTemporaryFile
    # object down to 0, which makes the file get deleted.
    # handle = None

    if os.path.exists(filename):
        print("File exists")
    else:
        print("File doesn't exist")

    filename = test_encoding()
    with open(filename, 'r') as f:
        print(f.read())

if __name__ == "__main__":
    main()
