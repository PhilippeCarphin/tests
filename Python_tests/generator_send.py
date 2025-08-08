

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


def rolling_average_gen():
    average = 0
    nb_elements = 0
    total = 0
    try:
        while True:
            value = yield average
            total += value
            nb_elements += 1
            average = total / nb_elements
    except GeneratorExit:
        return "Averager retval"


def test_rolling_average():
    averager = rolling_average_gen()
    next(averager)
    for n in range(1,100):
        current_average = averager.send(n)
        print(f"current_average = {current_average}")
    try:
        averager.throw(GeneratorExit())
    except StopIteration as e:
        print(f"Return value of generator: '{e.value}' ({type(e.value)})")

def main():
    test_my_gen()
    test_new_gen()
    test_rolling_average()

if __name__ == "__main__":
    main()
