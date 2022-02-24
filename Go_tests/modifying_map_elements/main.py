import pprint

MyMap = {"A": {1:1, 2:2}, "B": {1:2, 2:3}, "C": "This is a string"}
print("MyMap : ")
pprint.pprint(MyMap)

b = MyMap["B"]
c = MyMap["C"]

d = c.replace("i", "I")
print(f"c.replace('i', 'I') : {d}")
print(f"after c.replace('i', 'I') c = {c}")
print("MyMap after replace : ")
pprint.pprint(MyMap)

# c still points to the same string object "This is a string"
# the map stores pointers to objects and we put a different pointer there.
# We can't modify MyMap["C"] through a variable because the object "This is a string"
# is immutable.  If it were mutable, a list, a map, or any type that is mutable
# then we could change it.  But calling methods on c cannot modify the object
# pointed to by c because all string methods don't modify the object, they
# return modified copies.
#
# And we see that c is not modified after the replace call because that's not
# how it works.  There are no methods that modify strings in-place nor are there
# for tuples.
#
# So although we deal with pointers, the variable c is not a pointer to a part
# of the map, it is a copy of the pointer that is currently stored in the map
# If the object were mutable, then c could be used to "modify" the map as is
# done with b.

b[1] = 4

print("MyMap after b[1] = 4")
pprint.pprint(MyMap)

