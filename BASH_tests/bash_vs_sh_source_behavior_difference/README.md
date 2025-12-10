This demonstrates a difference in behavior between bash and sh (at least the
bash and sh on the system where I made this test) when sourcing a file that
contains syntax errors.

For each way of running/sourcing `source_syntax_error.sh`, I will write yes
or no for both shells to indicate whether the print at the end was seen.

- `<shell> -c "$(cat source_syntax_error.sh)"`        : Bash=yes, Sh=no
- `<shell> -c "source source_syntax_error.sh"`        : Bash=yes, Sh=no
- `<shell> source_syntax_error.sh"`                   : Bash=yes, Sh=no
- `$ ./source_syntax_error.sh` (interactively)        : Bash=yes, Sh=no
- `$ source ./source_syntax_error.sh` (interactively) : Bash=yes, Sh=yes

As we can see, Bash and Sh behave differently in every situation except one.

I made this test because I have a python tool that finds the modifications made
to the environment by a command which is usually a source command.  *CORRECTION*
I had a python tool that did this which was cringe and now I have a pure BASH 
tool [env-diff](https://github.com/philippecarphin/env-diff) which is based.

It works by first saving a copy of the environment then with a script like

```
orig_env=...
script = f'''
    {command} >&2
    print_env_to_json
'''
result = subprocess.run(script, shell=True, stdout=PIPE)
if result.returncode != 0:
    print(f"non-zero return code {result.returncode}")
new_env = json.loads(output)
compare(orig_env, new_env)
```

I tried it with `command = 'source some_file'` that did a source of something
that ended up sourcing a file that contained a syntax error.  The final command
that sourced the file with a syntax error had a `2>/dev/null` which further
hindered me.

My python script printed that the return code was 2 however when I ran `source
some_file` in my interactive shell, the return code was 0.

After trying a bunch of things, I thought maybe it's because the `subprocess.run()`
function uses `sh` instead of `bash` (I thought it would have used my user's
configured shel).

So I launched `sh` and typed `source some_file` at the prompt and got no error.
Finally, not knowing what else to try, I decided to change my `subprocess.run`
call to

```
subprocess.run(["/bin/bash", "-c", script], stdout=PIPE)
```

and to my delight, I got the behavior I wanted.  At that point, I was on to
something.  I looked at the code of subprocess.run() and found that when
passing a string and using `shell=True`, the string gets passed to `/bin/sh -c`
so I tried exactly that in my shell: `sh -c "source some_file"` and finally
reproduced the behavior that my Python script was having!


