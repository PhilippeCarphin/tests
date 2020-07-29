# Some basic shell functionalities can be found
# in the os.path module
import os
# The ones that aren't in there are very likely to be found in the shutil package
import shutil

new_dir = 'shell-builtins'
if os.path.isdir(new_dir):
    shutil.rmtree(new_dir)

os.system('touch initial_file')

os.rename('initial_file', 'renamed_file')
os.makedirs(new_dir, exist_ok=True)
os.rename('renamed_file', os.path.join(new_dir, 'renamed_file'))

# NOTE: Changing PWD is not advisa
shutil.copy2('ls-output.txt', new_dir)

print(f"{new_dir} is dir : {os.path.isdir(new_dir)}")
abs_path = '/asdf/bcde'
print(f'{abs_path} is absolute abs_path: {os.path.isabs(abs_path)}')
current_file = __file__ # this file
print(f'{current_file} is file : {os.path.isfile(current_file)}')
no_exists = 'no-exists'
print(f'{no_exists} is file : {os.path.isfile(no_exists)}')

link_path = __file__ + '.link'
os.link(__file__, link_path)
print(f'{link_path} is link : {os.path.islink(link_path)}')


os.environ['repo'] = 'A_REPO'
r = os.path.expandvars('~/Documents/$repo/$not_in_environ')
s = os.path.expanduser(r)
print(f'r = {r}')
print(f's = {s}')


# Other functions:
# shutil.copytree(src, dst)
# shutil.rmtree(path)
# os.remove()
# os.removedirs()
shutil.copytree(new_dir, new_dir + '_copy')

input("Before cleaning up, you may want to inspect the directories to see the effects of the command, press any key to cleanup")
try:
    os.removedirs(new_dir)
except OSError as e:
    print(f'OSError : {e}')
    print(f'ERROR: os.removedirs is like rm without the "-rf"')

os.remove(link_path)
shutil.rmtree(new_dir)
shutil.rmtree(new_dir + '_copy')