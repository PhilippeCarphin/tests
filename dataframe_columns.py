

column1 = ['a', 'b', 'c']

column2 = ['A', 'B', 'C']

import pandas as pd

df = pd.DataFrame(column1)

df['column2'] = column2

print(df)
