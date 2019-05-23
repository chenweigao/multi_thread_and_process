import asyncio

async def main():
    print('Hello...')
    await asyncio.sleep(1)
    print('..world!')

asyncio.run(main())



async def nested():
    return 42

async def run_nested():
    nested()  # 会报错，因为协程是可等待对象
    print(await nested())

asyncio.run(run_nested())

'''
并发处理多任务举例，计算阶乘，使用 asyncio.gather()
'''
async def factorial(name, number):
    f = 1
    for i in range(2, number + 1):
        print(f"Task {name} : compute factorial({i})...")
        await asyncio.sleep(1)
        f *= i
    print(f"Task {name}: factorial({number}) = {f}")

async def factorial_main():
    await asyncio.gather(
        factorial("A", 2),
        factorial("B", 3),
        factorial("C", 6),
    )

asyncio.run(factorial_main())