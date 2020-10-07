
def open_file(f):
    try:
        print(f'opening file')
        raise ValueError('value error')
    finally:
        print(f'closing file')

open_file('.profile')
print('end of program')
