#o==========
#!/usr/bin/env python3
# Doit produire ce fichier CSV /home/avions/outils/python/series_avions_listes.csv

import sys
import numpy as np
import pandas as pd

from pathlib import Path
from glob import glob

print ( ' on commence' )

files = glob('/home/yuz000/data/maestro_archives/allowlist_ai01_pre/monitoring/lists/202208*_ai_dynamic.txt')
all_dfs = []
for f in files[:10]:
    df = pd.read_csv(f, delimiter=r'\s+', skipinitialspace=True, names = ['id_stn','Vents','Temperature','Humidite'], dtype = {'id_stn':str, 'Vents':str, 'Temperature':str, 'Humidite':str})
    filename = Path(f).stem
    time = pd.to_datetime(f'{filename[0:4]}-{filename[4:6]}-{filename[6:8]}T{filename[8:10]}Z')
    df['time'] = time
    # print(f"file = {f} ========================================")
    # print(df.head())
    all_dfs.append(df)
new_df = pd.concat(all_dfs,ignore_index=True)

total_df = pd.DataFrame()
total2_df = pd.DataFrame()

#==============================================================================
date_rng = pd.date_range(start='08/01/2022', end='08/31/2022', freq='6H')
#==============================================================================

print("=========================================================")
print("listes_df")
listes_df=new_df.sort_values(['id_stn','time'],ascending=[True,True])
listes_df["elelist"] = listes_df["Vents"] + listes_df["Temperature"] + listes_df["Humidite"] 
listes_df['prev_id_stn'] = listes_df.id_stn.shift(1)
listes_df['prev_list']   = listes_df.elelist.shift(1)
listes_df['Diff1']       = np.where( listes_df['elelist'] == listes_df['prev_list']   , 0, 1)
listes_df['Diff2']       = np.where( listes_df['id_stn']  == listes_df['prev_id_stn'] , 0, 1)
listes_df['Diff3']       = listes_df['Diff1'] + listes_df['Diff2']
listes_df['Diff3']       = np.clip(listes_df['Diff3'].to_numpy(), a_max=1, a_min=None)
print(listes_df.head())
# gb = liste_df[liste_df['Diff3'] != 0]
gb = listes_df.groupby(by="id_stn")
# print("========================================================")
# print("gb : ")
gbt = gb['Diff3']

total_df['totals']       = gb['Diff3'].sum()
total_df['time'] = gb['time'].first()
print("========================================================")
print("total_df['totals'] =====================================")
print(total_df.head())

#total2_df['totals']       = listes_df.groupby(by="time")['id_stn']

#total2_df['totals']       = total_df.groupby(by=['id_stn','Diff3']).sum()
#with pd.option_context('display.max_rows', None,
#                         'display.max_columns', None,
#                         'display.precision', 3,
#                         ):
#      print( total_df['totals'] )
total_dfs=total_df.sort_values(['totals'],ascending=[False] )

stnll=list( total_dfs.index )
total= list( np.array( total_dfs['totals'] ) )

# print(f"stnll='{stnll}'")
# print(f"total='{total}'")


# ---------------------- SECTION DE TEST ---------------------------------------#
# def cat_vals(v,t):
#     return ''.join([str(v),str(t)])

# table_heatmap = list(map(cat_vals, date_rng, total_dfs['totals']))

# d = {'date':date_rng,'station':total_dfs['totals']}
# table_heatmap = pd.DataFrame(d)

# ---------------------- SECTION DE TEST FIN ------------------------------------#


# print ( ' lengts =',  len(stnll) ) 
# print ( ' dflistcols=', listes_df.columns )
# print ( ' dflisttypes=', listes_df.dtypes )
# for i in range( 1000 ) :
#   id=stnll[i]  
#   if (  total[i] >= 8):
#      print(i,id,total[i])
#      df_stn= listes_df[['elelist','time']].loc[ listes_df['id_stn']==stnll[i]]

#      #===========Remplir un tableau avec toujours 124 dates avec un join left ou right======
#      #=========== tu dois generer timeseries   avec  date_rng ======
# #     df_join=timeseries.join(df_stn,how=... ,lsuffix='_caller', rsuffix='_other')
#      #==============================================================================

#      print (' stnidtotal=',id,total[i], df_stn.shape)
# #     with pd.option_context('display.max_rows', None,
# #                          'display.max_columns', None,
# #                          'display.precision', 3,
# #                          ):
# #       print(   df_stn )
# print ( ' SUMTOTAL=', sum(total)  )
# for j in range(20):
#    jj=0
#    for i in range ( len (total) ):
#       if  total[i] == j :
#        jj=jj+1
#    print( 'j jjtot=',j,jj)

df = pd.DataFrame(total2_df)
df.to_csv('test_listestable_ex8.csv')
