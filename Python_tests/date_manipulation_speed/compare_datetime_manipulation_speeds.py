import pandas as pd
import numpy as np
from datetime import timedelta, datetime
import time

#
# Create a one-column dataframe with NROWS rows
#
NROWS = 10000
r = np.random.randint(1691698370 - 10000, 1691698370, (NROWS))
df = pd.DataFrame(data=r, columns=['TIME'])
print("Initial dataframe")
print(df.head())

# Slow
def datetime_use_row_directly(row):
    """ Add one hour by converting to datetime object and adding a timedelta
    of one hour """
    # Since row only has one column, we don't need to do this:
    #   t = row['TIME']
    #   dt = datetime.fromtimestamp(t)
    # Instead, just this
    dt = datetime.fromtimestamp(row)
    dtt = dt + timedelta(hours=1)
    return int(dtt.timestamp())

# Fast
def datetime_extract_value_from_row(row):
    """ Add one hour by converting to datetime object and adding a timedelta
    of one hour """
    t = row['TIME']
    dt = datetime.fromtimestamp(t)
    dtt = dt + timedelta(hours=1)
    return int(dtt.timestamp())

# Slowest
def direct_timestamp_use_row_directly(row):
    """ Add one hour by adding 3600 to the row itself.  This one is ~10 times
    slower than the one using datetime and I have no idea why. """
    return row + 3600

# Fast
def direct_timestamp_extract_value_from_row(row):
    """ Add one hour to the row by doing +3600.  This one is about twice as
    fast as the one using datetime. """
    t = row['TIME']
    return t + 3600

def manipulate_row(row):
    """ Add one hour by converting to datetime object and adding a timedelta
    of one hour """
    # Since row only has one column, we don't need to do this:
    #   t = row['TIME']
    #   dt = datetime.fromtimestamp(t)
    # Instead, just this
    dt = datetime.fromtimestamp(row)
    dtt = dt + timedelta(hours=1)
    row['TIME'] = int(dtt.timestamp())

def print_time(s,t1,t2):
    print(f"{s:>50}: {t2 - t1:-2.5f}")

t1 = time.clock()
df1 = df.apply(datetime_use_row_directly, axis=1)
t2 = time.clock()

print_time('Using datetime_use_row_directly',t1,t2)

t1 = time.clock()
df2 = df.apply(datetime_extract_value_from_row, axis=1)
t2 = time.clock()

print_time('Using datetime_extract_value_from_row',t1,t2)

t1 = time.clock()
df3 = df.apply(direct_timestamp_use_row_directly, axis=1)
t2 = time.clock()

print_time('Using direct_timestamp_use_row_directly',t1,t2)

t1 = time.clock()
df4 = df.apply(direct_timestamp_extract_value_from_row, axis=1)
t2 = time.clock()

print_time('Using direct_timestamp_extract_value_from_row',t1,t2)

t1 = time.clock()
df.apply(manipulate_row, axis=1)
t2 = time.clock()

print_time('In place manipulation of row',t1,t2)


print(df1.head())
print(df2.head())
print(df3.head())
print(df4.head())
print(df.head())
