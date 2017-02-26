"""
Tours of Hanoi: Google it.  If you have stacks

    *       *       *
    *       *       *
    *       *       *
    *       *       *
    *       *       *
   src    other    dst

then to move a stack of N discs from src to dst, you must
    move the N-1 top discs from src to other, then
    move the lowest disc to dst, then
    move the N-1 discs
from other to dst.

So that H(N) = H(N-1) + 1 + H(N-1) = 2*H(N-1) + 1 with H(1) = 1.

One notices that H(N) = 2^N - 1.  We can prove this recursively.

Base case:
    H(1) = 1 = 2^1 - 1.

Recursion:
    Suppose that H(N-1) = 2^(N-1) - 1
    Then
        H(N) = 2*H(N-1) + 1
             = 2*(2^(N-1) - 1) + 1
             = 2^N - 2 + 1
             = 2^N - 1.
"""

""" Iterative calculation of hanoi function"""
def hanoi(n):
    i = 1
    hanoi = 1
    while i <= n:
        print hanoi
        hanoi = 2* hanoi + 1
        i += 1

""" Recursive calculation of hanoi function"""
def hanoi_2(n):
    if n == 1:
        return 1

    h = hanoi_2(n-1)
    return 2*h + 1

hanoi(8)
print "================"
for i in range(1,9):
    print(i,hanoi_2(i))

