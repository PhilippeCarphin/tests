
import dask.array as da
for i in range(2):
    x = da.random.random((10000, 10000), chunks=(100, 100))
    y = x + x.T
    z = da.sin(y)
    z.compute()