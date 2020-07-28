import sqlite3
import calendar
import pandas as pd
import datetime
import locale

# Uncomment to see days in French
# locale.setlocale(locale.LC_ALL, 'fr_CA')

# it will default to the system locale so for our system, this is redundant
# locale.setlocale(locale.LC_ALL, 'en_US')

prognos_db = '/home/stat999/sitestore3/prognos/forecasts/met/2019101600.db'
forecast_query = 'SELECT * FROM forecast WHERE forecast IS NOT NULL'
conn = sqlite3.connect(prognos_db)

df = pd.read_sql_query(forecast_query, conn)
# scalaire -> scalaire
def station_to_name(station):
    if station.startswith('A1'):
        return 'PHIL'
    else:
        return 'JACQUES'

# scalaire -> scalaire
def unixtime_to_JMT(unixtime):
    t = datetime.datetime.utcfromtimestamp(unixtime)
    # BAD:
    # weekday_name = calendar.day_name[t.weekday()]
    # return f'~{t.year}~{t.month}~{t.day}~{t.day}~{weekday_name}~{t.strftime("%a")}~{t.strftime("%A")}'

    # GOOD:
    # see https://docs.python.org/3/library/datetime.html#strftime-strptime-behavior
    return t.strftime('%Y~%m~%d~(%A)-%H:%M:%S')

# Creating a new column from an existing one using map and a scalar->scalar function
df['name'] = df['station'].map(station_to_name)
df['jmt'] = df['run_date'].map(unixtime_to_JMT)

# row -> scalaire
def doer(x):
    t = datetime.datetime.utcfromtimestamp(x['run_date'])
    dt = datetime.timedelta(hours=x['fcst_hour'])
    new_time = t + dt
    return new_time.strftime('%Y~%m~%d~%H:%M:%S')

# scalaire -> scalaire
def time_adder(unixtime):
    dt = datetime.timedelta(days=8.1, seconds=3.2)
    t = datetime.datetime.utcfromtimestamp(unixtime)
    return t + dt

# Creating a new column from existing columns using row->scalar function
df['NEW_COL'] = df.apply(doer, axis=1)

# Example of using time deltas
df['SUM_COL'] = df['run_date'].map(time_adder)

print(df.head())




