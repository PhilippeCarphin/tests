#!/usr/bin/env python3
import pandas as pd

""" This test demonstrates the use of the apply method of
pandas DataFrame objects to apply a function to each row
of a data frame.

df.apply() takes a function as its first parameter and calls
it once for each row of the data frame.

When df.apply() calls the function, it passes it a row of
the data frame and expects it to either return a new row
or a scalar value.

If the passed function returns scalars, the return value of
df.apply() will be a column formed by the scalar values
returned by the function.

If the passed function returns rows, the return value of
df.apply will be a dataframe formed by the rows returned
by the function.
"""


dict_for_data_frame = {
        "name": [ "Phil", "Paul", "Grace", "Emmy" ],
        "points" : [ 1,     2,       3,     4 ],
        "age" : [ 37,      34,     100,    150]
}

df = pd.DataFrame(dict_for_data_frame)
print(df)

def func_to_apply(row):
    # When not sure, print the function's arguments to see how df.apply calls it
    print("== in func_to_apply ============================================")
    print(f"row is of type {type(row)}")
    print(row)
    return row['points'] * row['age']

# Here result is single column formed from the scalar values
# returned by func_to_apply.
result = df.apply(func_to_apply, axis=1)
print(result)

# We can add this row to our existing dataframe df:
df['x'] = result
# or normally we would do this in one line by doing
# df['x'] = df.apply(func_to_apply, axis=1)
# but instead we assigned the return value of df.apply
# to the variable result so we could print it.

def func_to_apply2(row):
    if row['age'] == 37:
        row['allcaps'] = 3.1415
        row['age'] = 37.0
        return row
    row['x'] = row['points'] * row['age']
    row['allcaps'] = row['name'].upper()
    return row

# Here result2 is a whole dataframe formed by all the rows
# returned by func_to_apply2
# We notice that for some rows, we don't set a value for the 'x'
# column and in that case, the column contains NaN for that row.
df = pd.DataFrame(dict_for_data_frame)
result2 = df.apply(func_to_apply2, axis=1)
print(result2)

# Since columns must have uniform type, we may end up with a
# column whose dtype is object if we mix types like it is done
# in func_to_apply2 or we may end up changing the type of the
# whole column like setting row['age'] = 37.0 changes the whole
# column to floating point.
# A column of strings will generally have dtype = object because
# the type does not refer to the type of a python object but to
# the `dtype` of a numpy array.
print(f"type of column age: df: {df['age'].dtype}, result2: {result2['age'].dtype}")
print(f"type of results['allcaps']: {result2['allcaps'].dtype}")
print(f"type of results['name']: {result2['name'].dtype}")

