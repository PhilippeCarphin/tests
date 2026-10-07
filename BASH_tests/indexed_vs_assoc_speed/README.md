This is a demonstration different ways of iterating over arrays in BASH in
relation to the code that injects descriptions into completion candidates.

Because this way of iterating:
```bash
    comp=(comp1 comp2 ...)
    desc=([comp1]=desc1 [comp2]=desc2 ...)
    for((i=0;i<${#_comp_array[@]};i++)); do
        c=${comp[i]}
        d=${desc[${comp}]}
```
does a lookup in an associative array at each iteration, it migh be tempting
to think that this way:
```bash
comp=(comp1 comp2 ...)
desc=(desc1 desc2 ...)
    for((i=0;i<${#comp[@]};i++)); do
        c=${comp[i]}
        d=${desc[i]}
```
might be faster.

Indeed in C, it sure would be but with the way indexed arrays are implemented
in BASH, I don't know.

What surprised me is that because that this one:
```bash
    comp=(comp1 comp2 ...)
    desc=([comp1]=desc1 [comp2]=desc2 ...)
    for c in "${comp[@]}" ; do
        d=${desc[$c]}
    done
```
is about twice as fast as the other ones!

Apparently arrays are implemented as linked lists which also hold a "last
accessed element" pointer to speed up sequential access.  So accessing them
in order should be fast.

However the `for x in ...` is much faster because there is no indexed access
for the first array.  No lookups, we just get fed sequential array elements.

Even more surprising, discussing with an AI, it pointed out the "last accessed
element" thing, so I wondered if traversing the array in reverse would make
it slower.

It made it faster!  It seems that in the `for((...))`, the condition is re
evaluated at every iteration which means that with `for((...;i<${n};...))`
looking up the value of `${n}` makes a difference.

Since the reverse one has a hardcoded value, that's one less lookup per
iteration.  And we can confirm that the order is not what makes the difference
by comparing `indexed-constant-condition.sh` with `indexed.sh`.  The only
difference is the hardcoded `72`

And that makes an ~8% difference in the timings.
