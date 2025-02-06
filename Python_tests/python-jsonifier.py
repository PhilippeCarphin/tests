f = open("f", 'rb')

def tokensa():
    while True:
        state = 'base' # 'maybe-completing-chunk'
        buf = f.read(100)
        chunks[1] += bytes([0])
        if buf.startswith(0):
            return
        print(chunks)
        if buf == None:
            yield from chunks[:-1]
        break
def tokens():
    i = 0;
    buf = bytes()
    while True:
        i += 1;
        c = f.read(1)
        print(f'c={c}')
        if c == b'\x00':
            yield buf
            buf = bytes()
        elif c == b'':
            yield buf
            return
        else:
            buf += c
            print(f"buf={buf}")
        if i > 18:
            return

print(list(tokens()))

f.close()
