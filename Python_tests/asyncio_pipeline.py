import asyncio

t = 0.1

async def first(a):
    b = a * 2
    await asyncio.sleep(t)
    return b
async def second(a):
    c = a * 3
    await asyncio.sleep(t)
    return c
async def third(c):
    o = c * 4
    await asyncio.sleep(t)
    return o

async def pipeline(i):
    a = i
    b = await first(a)
    c = await second(b)
    o = await third(c)
    return o

async def main():
    for i in range(10):
        o = await pipeline(i)
        print(o)


async def feed(outQ, n):
    print("feed()")
    for a in range(n, n+10):
        await outQ.put(a)
    if wait:
        await outQ.join()

async def first_w(inQ,outQ):
    print("first_w()")
    while True:
        a = await inQ.get()
        b = await first(a)
        await outQ.put(b)
        if wait:
            await outQ.join()
        inQ.task_done()

async def second_w(inQ,outQ):
    print("second_w()")
    while True:
        b = await inQ.get()
        c = await second(b)
        await outQ.put(c)
        if wait:
            await outQ.join()
        inQ.task_done()

async def third_w(inQ,outQ):
    print("third_w()")
    while True:
        c = await inQ.get()
        o = await third(c)
        await outQ.put(o)
        if wait:
            await outQ.join()
        inQ.task_done()

async def consume(inQ):
    print("consume()")
    while True:
        o = await inQ.get()
        print(f"got o = {o}")
        inQ.task_done()

# I'm really not sure on how the proper way is to wait for the things to have
# gone through the pipeline.  You're supposed to join() on the queues in a
# producer-consumer with queues type of context but I'm just trying a bunch of
# stuff.
wait = False
async def true_pipeline():
    # I tried to create a set of global queues.  It seems that you can't do that.
    # I was getting errors like "outQ.put(a) ... got Future <Future pending>
    # attached to a different loop.
    #
    # I take that to mean that the queue has to get created after we have
    # started the main loop. And that is why even in the smallest toy examples
    # people always declare their queues inside functions and pass them as
    # parameters.
    #
    # So create some queues
    s = 1
    aQ = asyncio.Queue(s)
    bQ = asyncio.Queue(s)
    cQ = asyncio.Queue(s)
    oQ = asyncio.Queue(s)

    # Create some worker tasks
    feed_task = asyncio.create_task(feed(aQ, 3))
    first = asyncio.create_task(first_w(aQ,bQ))
    second = asyncio.create_task(second_w(bQ,cQ))
    third = asyncio.create_task(third_w(cQ,oQ))
    cons = asyncio.create_task(consume(oQ))

    # Not super sure what the best thing to do.  Raymond Hettinger pointed out
    # that workers are by their nature infinite loops, so don't wait on workers,
    # but rather wait on the queues.
    await feed_task
    await aQ.join()
    await bQ.join()
    await cQ.join()
    await oQ.join()

    # This second one goes twice as fast because we are launching new workers
    # and using the same queues there will be two first_w, second_w, third_w and
    # consume going all at once.
    # await asyncio.gather(feed(aQ, 8), first_w(aQ,bQ), second_w(bQ,cQ), third_w(cQ, oQ), consume(oQ))

async def true_pipeline_gather():
    # This function shows that the reason the second run using gather in the
    # true_pipeline() function above was faster is indeed because there were
    # two sets of workers reading and producing on the same queues.
    s = 1
    aQ = asyncio.Queue(s)
    bQ = asyncio.Queue(s)
    cQ = asyncio.Queue(s)
    oQ = asyncio.Queue(s)

    await asyncio.gather(feed(aQ, 8), first_w(aQ,bQ), second_w(bQ,cQ), third_w(cQ, oQ), consume(oQ))
if __name__ == "__main__":

    # asyncio.run(main())
    asyncio.run(true_pipeline())
    # asyncio.run(true_pipeline_gather())
