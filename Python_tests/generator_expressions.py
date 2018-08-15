"""This test demonstrates the use of the 'seen' idiom for complex iteration
with python generators

Contrarily to iterating over the members of a container, changing the
container during iteration is likely to cause exceptions, using a generator
works well.

The key is to note that

    gen = (i for i in numbers if i not in seen)

does not create a list. It creates a generator that will go through the
values in numbers.  But for each iteration, the current state of seen will be
examined.

When i = 1, we add 1 and 2 to seen.  When the for loop requests a next
value from the generator, the generator looks at the next value in numbers,
which is in seen, so it looks at 3, which is not in seen.  It then yeilds
the value 3.
"""
numbers = [1, 2, 3, 4, 5, 6]

seen = set()

for i in (i for i in numbers if i not in seen):
    print("i = {}".format(i))
    seen.add(i)
    seen.add(2*i)

""" Without generator expressions, the result is different.  List comprehensions
are nothing more than a special syntax for building a list.  Therefore, before
loop starts, the list comp is evaluated with seen being empty."""
seen = set()
for i in [i for i in numbers if i not in seen]:
    print("i = {}".format(i))
    seen.add(i)
    seen.add(2*i)
