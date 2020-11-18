
import asyncio

async def say_after(t, m):
    a = await return_after_sleep("thing", t)
    print(f'{m} (a={a})')

async def return_after_sleep(ret, t):
    await asyncio.sleep(t)
    return ret

async def main():
    print('started main')
    task1 = asyncio.create_task(
        say_after(3, 'hello'))

    task2 = asyncio.create_task(
        say_after(2, 'world'))

    print('waiting for tasks to finish')

    await task2
    await task1

    print('finished')

asyncio.run(main())


