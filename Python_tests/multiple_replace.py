import re

d = {
    r'ab*c': r'ABC',
    r'de*f': r'DEF'
}
s = 'abbbbcdeeeeeeeeeeeeeeeeeeeeeeeef'

def multiple_replace(d, s):
    master_regex = f'({"|".join(d.keys())})'
    r = re.compile(master_regex)
    global match
    match = r.match(s)
    print(r.findall(s))

multiple_replace(d, s)

def multi_sub(pairs, s):
    """ From https://stackoverflow.com/a/61952495/5795941 """
    def repl_func(m):
        # only one group will be present, use the corresponding match
        return next(
            repl
            for (patt, repl), group in zip(pairs, m.groups())
            if group is not None
        )
    pattern = '|'.join("({})".format(patt) for patt, _ in pairs)
    return re.sub(pattern, repl_func, s)

pairs = list(d.items())
print(pairs)
print(multi_sub(pairs, s))

dg = [
    (r'a(b*)c', r'A\1C'),
    (r'd(e*)f', r'D\1F')
]

def multi_sub_g(repls, s):
    output = s
    for patt, repl in repls:
        output = re.sub(patt, repl, output)
    return output


print(multi_sub_g(dg, s))
