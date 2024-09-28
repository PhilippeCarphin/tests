
def is_even(n):
    t = type(n)
    if not isinstance(t, int):
        raise TypeError(f"Function expects int, not {t.__name__}")
    return i % 2 == 0
