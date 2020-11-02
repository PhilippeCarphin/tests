import submodule

try:
    np.zeros((100,100))
    print("Used numpy function")
except NameError as e:
    print(f'{type(e)}: {e}')
    print(f"Even though submodule import numpy as np, we can't access numpy here")
