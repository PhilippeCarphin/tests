#!python
""" This test shows that python can represent arbitrarily large integers.
Indeed the first function: exponentiate is garanteed to work because it takes
the remainder mod n at each multiplication of res by a.

Testing the second function and comparing results with the first one shows that
exponentiate2 returns the correct result.  An internet search confirms that
python can represent huge integers like 2**311.
"""

""" Using RSA cryptography: figuring out whether I need to reduce mod n every
time I multiply or if I can just do (a^e)%n.  For sure in C there would be some
overflowing and I would have to do it the first way, but either python is smart
or can handle arbitrarily large numbers """
def exponentiate(a,e,n):
    res = 1
    for i in range(e):
        res = res * a
        res = res % n
    return res

def exponentiate2(a,e,n):
    return (a**e)%n


if __name__ == "__main__":
    print "2^4 = " + str(exponentiate(2,4,1000))
    print "2^4 = " + str(exponentiate2(2,4,1000))
    print "2^311 = " + str(exponentiate(2,311,10000000000000000000000000))
    print "2^311 = " + str(exponentiate2(2,311,1000))



