import io
import time
import subprocess

f = io.StringIO()

f.write("abcd initial text data")

# f.mode = "a"
# f.seek(io.SEEK_END)
f.write("efgh more stuff")

# f.close()

def send_email(to, content):
    p = subprocess.Popen(["mail", "-s", "python mail test", "philippe.carphin@ec.gc.ca"], universal_newlines=True, stdin=subprocess.PIPE)
    p.stdin.write("HELLO\n")
    p.stdin.write(content)
    p.stdin.write("\ndone\n")
    p.stdin.close()
    p.wait(4)



send_email("philippe.carphin@ec.gc.ca", f.getvalue())
print(f.getvalue())
