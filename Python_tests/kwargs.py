import inspect


class PySpookiImplementationError(Exception):
    pass


class PySpookiArgumentError(Exception):
    pass


def make_unix_command_string(command_name, argspec, kwargs):
    """ Create a unix-style command from a function call.

    ARGUMENTS

        argspec Dictionary of argname: argdefault pairs.

        kwargs The arguments of the function call.

    EXCEPTIONS

    ArgumentError :
            arg has no value and default is None
            arg is a flag but it's value is not True or False
            arg has been given None value
    """
    def is_flag(arg):
        return argspec[arg] is False

    words = [command_name]
    for arg in argspec:

        if arg in kwargs:
            argvalue = kwargs[arg]
            del kwargs[arg]

            if is_flag(arg):
                if argvalue not in [True, False]:
                    raise ArgumentError("Flag argument {} can only be True or False".format(arg))
                if argvalue is True:
                    words.append("--{}".format(arg))
            elif argvalue is not None:
                words.append("--{} {}".format(arg, argvalue))
            else:
                raise ArgumentError("Functions cannot have None for argument values")
        else:
            if argspec[arg] is None:
                raise ArgumentError("Argument {} is required for".format(arg, command_name))
            else:
                words.append("--{} {}".format(arg, argspec[arg]))

    if kwargs:
        raise PySpookiArgumentError("Arguments {} are not part of the specification".format(list(kwargs)))

    return ' '.join(words)


def make_unix_adapter(func):
    """Use func as a specification for arguments to 

    ARGUMENTS

    func: A function that specifies an interface for a spooki plugin

    RETURNS

    new_func: A keyword argument function that construcst a unix command and
    sends it to the syste unix command and sends it to the system.

    """
    command_name = func.__name__
    argspec = inspect.getargspec(func)
    argnames = argspec[0]
    argdefaults = argspec[3]
    if len(argdefaults) != len(argnames):
        raise PySpookiImplementationError("Command {} must have default values for all arguments")
    if True in argdefaults:
        raise PySpookiImplementationError("Command {} arguments cannot have a default value of True")

    defaults = dict(zip(argnames, argdefaults))

    def new_func(args, **kwargs):
        unix_cmd = make_unix_command_string(command_name, defaults, kwargs)
        print("os.system(\"{}\")".format(unix_cmd))
        # os.system(unix_cmd)

    new_func.__name__ = func.__name__
    new_func.__doc__ = func.__doc__
    return new_func


@make_unix_adapter
def decorated_arg_function(humeur=None,
                           couleur='piss-bucket',
                           bonjour=False):
    """EXAMPLE SPECIFICATION : A function that doesn't do anything.

    It is decorated to make a function that checks the argumensts, builds a
    string and makes a call to the spooki plugin by the same name.

    humeur is a mandatory argument, an exception will be raised if a call is
    made without it.

    couleur has a default value, it doesn't need to be specified.

    bonjour is a flag if it is set to true then the flag will be appended
    to the command

    """
    pass

@make_unix_adapter
def windchill(temperature="cold", pressure=130, some_flag=False):
    pass

class RepoList:
    def __init__(self, filename=None):
        if filename is None:
            self.repos = [
                {'id': 0, url : 'something.com', other : {}},
                {'id': 1, url : 'something1.com', other : {}},
                {'id': 2, url : 'something2.com', other : {}},
                {'id': 3, url : 'something3.com', other : {}}
            ]
        else:
            with open(filename, 'r') as f:
                self.repos = json.loads(f.read())

    def clone_into(self, dir):
        if not check_safe_for_clone(dir):
            raise FuckOffException

        for repo in self.repos:
            git_clone(url="asdf")

def git_clone(url=None, dir=dir):


class StudentRepo:
    def __init__(self, url, directory):
        self.dir = directory
        self.url = url
        self.repo = RepoWrapper(directory)
        self.init_repo_wrapper()

    def init_repo_wrapper(self):
        self.repo.clone(url=self.url)

    def clone(self):
        git_clone_cmd(url=self.url, dir=self.dir)

    def checkout_assignment(self, assignment):
        # output = self.repo.checkout("last commit before date {}".format(assignment.due_date))
        # Do stuff with output
        # return {'result': 'OK', 'other': None}
    def build_assignment(self, assignment):
        # build_dir = assignment.build_dir
        # change_dir
        # run assignment build command
        # return {'result': 'OK', 'other': None}

    def __str__(self):
        return("{}:{}".format(self.__class__, self.__dict__))

class Teacher:
    def __init__(self, directory=None)
        self.sections = [
            Section(1),
            Section(2)
        ]
        self.directory = os.getcwd()

    def init_all(self):
        self.do_all(self.init_student_repo)

    def init_student_repo(self, student_repo)
        # They have a url, but I decide what directory their repo will have
        # make student repo object from input file



    def section_do(self, section, function):
        for student_repo in section:
            function(self, student_repo)

    def do_all(self, function):
        for section in self.sections:
            self.section_do(section, function)

class Section:
    def __init__(self):
        self.info_file = info_file
        self.students = {
            'an_id': {
                'name': 'hello'
            },
            'another_id': {
                'asdf': 'asdf'
            }
        }

    def load_file(self, filename):
        with open(filename, 'r') as f:
            self.students = json.loads(f.read())
        self.info_file = filename

    def save_file(self, filename):
        with open(filename, 'w') as f:
            f.write(json.dumps(self.info))

    def __iter__(self):
        return iter(self.info)

class Assignment:
    def __init__(self):
        self.data = {}
        self.build_command = ""
        self.spec = {}
        self.result = {}

    def run_build():
        # output = subprocess.whatever(someCommand)
        return self.parse_build_output(output)

    def parse_build_output():
        output_data = {}
        # stuff
        return output_data

class Student:
    def __init__(self):
        self.assignmetns = []
        self.grading_dir = "~/Documents/Cours/INF1995"

class Projet1Teacher(Teacher):
    def __init__(self, files=None):
        super().__init__(files)

    def init_student(self, student)

    def check_assignment(self, student, assignment):
        verify_stuff, change student data, each student has assignments.

    def build_assignment(self, student, assignment):
        # change dir to "os.path.join([student['dir'], assignment['subdir']])"
        # 
        # in INF1995 it't go to the dir and run make
        # parse output

    def init_grading(self, student, assignment):
        # write Json.dumps(assignment.spec) to file in student.dir



    

def import_csv(filename):
    with open(filename, 'r') as f:
        csv_reader = csv.reader(f.read())

    for row in csv_reader:
        # id = ...
        # url = ...
        # ... = ...



if __name__ == "__main__":
    print("CALLING DECORATED FUNCTION")
    decorated_arg_function(humeur='piss-bucket', couleur='rouge', bonjour=True)
    print("CALLING DECORATED FUNCTION")
    decorated_arg_function(humeur='Joyeux', bonjour=True)
    print("CALLING DECORATED FUNCTION")
    decorated_arg_function(couleur='rouge', humeur='piss-bucket', bonjour=True)
    windchill()
    windchill(some_flag=True)
    # windchill(not_a_real_arg=8)
