

def my_gen():
    n = 0
    for a in range(10):
        ret = n*a
        print(f'yielding ret={ret}')
        yield ret
        print(f'waiting for d')
        d = yield
        print(f'Received d={d}')
        n += d


def test_my_gen():
    gen = my_gen()
    print('generator created')

    print('next -->')
    print(f'--> next got {next(gen)}')

    print('next -->')
    print(f'--> next got {next(gen)}')

    print('send 8 -->')
    print(f'--> send 8 got {gen.send(8)}')

    print('next -->')
    print(f'--> next got {next(gen)}')

    print('send 7 -->')
    print(f'--> send 7 got {gen.send(7)}')

def new_gen():
    acc = 0.0
    x = 0
    for i in range(10):
        acc += x
        r = acc * i * x
        print(f'  yielding r={r}, waiting for x ...')
        x = yield r
        print(f'  ...received x={x}')


def test_new_gen():
    ng = new_gen()
    print('next -->')
    print(f'--> next got {next(ng)}')

    print('send 0.3 -->')
    print(f'--> send 0.3 got {ng.send(0.3)}')
    print('send 0.4 -->')
    print(f'--> send 0.4 got {ng.send(0.4)}')


def main():
    test_my_gen()
    test_new_gen()

if __name__ == "__main__":
    main()
