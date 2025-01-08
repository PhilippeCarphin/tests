Cool techniques for completion

# `-f`: Printing a message during completion

Normally printing to the shell where completion happens messes up the output
but this can be solved by reprinting the current line `COMP_LINE`.

Double-tab already reprints the current line so we use `COMP_TYPE` to only
reprint the current line when in single-tab completion.

# `-F`: Using fzf

# `-c`, `-v`, `-V`: Spinners for long candidate acquisition

- Turning off the cursor and turnign it back on with `\033[?25l` and `\033[?25h`
  respectively.  If function execution is interrup before the cursor is turned
  back on by pressing `C-c` while candidates are being "acquired", the cursor
  stays gone so I'm not sure this is a valuable technique
- Caching the values.  With no way to invalidate the cache, this is also of
  questionable value

# `-C`, `-Z`: Using a drawn picker

A nice experiment in cursor manipulation using techinques learned while exploring
fzf.  The `-C` one is a short list and the `-Z` one is a long list.  Of course
fzf is way better but I used this to better understand how fzf works.

