def fizz_buzz(n):
    """ This one checks an intermediate value """
    output = ''
    if n % 3 == 0:
        output += 'fizz'
    if n % 5 == 0:
        output += 'buzz'
    if output == '':
        output = str(n)
    return output

def fizz_buzz_2(n):
    """ This one checks the same thing twice """
    if n % 3 == 0:
        if n % 5 == 0:
            return 'fizzbuzz'
        else:
            return 'fizz'
    else:
        if n % 5 == 0:
            return 'buzz'
        else:
            return str(n)


for i in range(1,16):
    print(fizz_buzz_2(i))
