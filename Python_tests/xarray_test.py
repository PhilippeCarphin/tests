import xarray
import numpy as np
import pandas as pd
import rmn

input_file = "/home/saz001/input_files/stationary_jing/stat_240"
def sep(s):
    print(f"================================ {s} =========================================")
def subsep(s=""):
    print(f"-------------------------------- {s}")

def find_descriptors(file, record):
    correspondence = {"ip1": record.ig1, "ip2": record.ig2, "ip3": record.ig3}
    try:
        tic_tic = next(file.new_query(nomvar=">>", **correspondence))
        tac_tac = next(file.new_query(nomvar="^^", **correspondence))
    except StopIteration:
        return None

    return tic_tic, tac_tac

#
# Read all TT records into a single numpy array in order of IP1's
#
with rmn.fst24_file(input_file) as f:
    tt_records = list((sorted(f.new_query(nomvar='TT'), key=lambda r: r.ip1)))
    cube = np.empty(
        (tt_records[0].ni, tt_records[0].nj, len(tt_records)),
        dtype=np.float32
    )
    for i, rec in enumerate(tt_records):
        cube[:,:,i] = rec.data[:,:,0]
    tic_tic, tac_tac = find_descriptors(f, tt_records[0])
    tic_tic.data
    tac_tac.data

#
# Create an xarray with this cube as its data
#
ip1s = [r.ip1 for r in tt_records]
longitudes = tic_tic.data[:,0,0]
latitudes = tac_tac.data[0,:,0]

xarr = xarray.DataArray(
    cube,
    # Give names to each dimension
    dims=("i", "j", "ip1"),
    # Values for indexing these dimensions
    coords={
        "i": longitudes,
        "j": latitudes,
        "ip1": ip1s
    }
)

#
# Demonstrate various ways of accessing the data from this XArray
#
ip1 = 40994464


sep("Index selection")
subsep("With index notation")
print(xarr[3,1,2])
subsep()
print(xarr[0,0,:])
sep("With isel")
print(xarr.isel(ip1=0))  # Read 'index 0 in the ip1 dimension', not 'has ip1 equal to 0'


sep("Access with labels")
print(xarr.loc[:,:,ip1])
subsep()
print(xarr.sel(ip1=ip1))  #  This one does really mean 'has ip1 equal to 40994464'


sep("Label selection with ranges")
print(xarr.loc[120.0, -17.8:-17.7, :])
subsep()
print(xarr.loc[:,-17.8:-17.7,40994464])
