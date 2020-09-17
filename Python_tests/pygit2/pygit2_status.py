import pygit2 as pg
import os
import sys
import datetime
import termcolor

from pprint import pprint
def get_toplevel(path):
    def is_repo(path):
        return '.git' in os.listdir(path)
    toplevel = path
    while not is_repo(toplevel):
        toplevel = os.path.dirname(toplevel)
        if toplevel == '/':
            raise Exception()
    return toplevel

def is_clean(repo):
    st = repo.status()
    # pprint(st)
    untracked = False
    modified = False
    for _, flags in st.items():
        if flags == pg.GIT_STATUS_WT_NEW:
            untracked = True
        elif flags == pg.GIT_STATUS_WT_MODIFIED:
            modified = True
    return {'modified': modified, 'untracked': untracked}


def ps1_phil(path):

    repo_path = get_toplevel(input_path)
    repo = pg.Repository(repo_path)
    state = is_clean(repo)
    if state['untracked'] or state['untracked']:
        color = 'yellow'
        head_commit_time = datetime.datetime.fromtimestamp(repo.get(repo.head.resolve().target).commit_time)
        time_since_last_commit = datetime.datetime.now() - head_commit_time
        untracked = '[UNTRACKED_FILES]'
    else:
        color = 'green'
        untracked = ''
    return termcolor.colored(
        f"({repo.head.shorthand}) {time_since_last_commit} {untracked}",
        color
    )

if len(sys.argv) > 1:
    input_path = sys.argv[1]
else:
    input_path = os.getcwd()

print(ps1_phil(input_path))