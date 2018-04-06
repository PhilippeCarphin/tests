def fizz_buzz(n):
    output = ''
    if n % 3 == 0:
        output += 'fizz'
    if n % 5 == 0:
        output += 'buzz'
    if output == '':
        output = str(n)
    return output


for i in range(15):
    print(fizz_buzz(i))
