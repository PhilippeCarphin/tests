#!/usr/bin/env python3

# beginning experimentation with the tokenize package

import tokenize

with open(__file__, 'rb') as f:
    tokens = list(tokenize.tokenize(f.readline))

for t in tokens:
    to_print = t.string if t.type != 4 else "\\n"
    print(f"{to_print:>25} {t}")
