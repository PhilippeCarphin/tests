class BitQuality:
    pass

def api_func(arg1: int, arg2: str):
    """ This is the docstring for api_func that I wrote

    :param arg1: The number of bits.
    :type arg1: int
    :param arg2: The flavor of bits.
    :type arg2: str

    :return: The quality of the bits
    :rtype: BitQuality

    """
    return BitQuality(f"arg1={arg1}, arg2={arg2}")
