This test evaluates the speed difference between using Python date functions
to manipulate a date versus doing the calculations ourselves.

The initial situation is adding one hour to each value in a time column of a
CSV file.  In the situation that led to this test, the time column stored dates
in UNIX timestamp form and the new CSV would also have dates stored in timestamp
form.  The CSV is read by pandas and some kind of `df.apply()` was used to
add one hour to the timestamps.

This test represents the function that we would pass to df.apply() that will
take the times.

Notice that multiple slightly different methods are used to modify the dataframe
with greatly varying results in time.

We see that the fastest dataframe method and the fastest timestamp methods are
quite close in speed.
