from threading import Thread, Lock
from time import sleep

class Account(object):

    def __init__(self):
        self._balance = 0
        self._lock = Lock()

    def deposit(self, money):
        # 存款
        self._lock.acquire()
        try:
            new_balance = self._balance + money
            sleep(0.1)
            self._balance = new_balance
        finally:
            self._lock.release()

    @property
    def balance(self):
        return self._balance

class AddMoneyThread(Thread):
    '''
    继承于 Thread 类的子类
    '''
    def __init__(self, account, money):
        super().__init__()
        self._account = account
        self._money = money

    def run(self):
        self._account.deposit(self._money)

def main():
    account = Account()
    threads = []

    for _ in range(100):
        t = AddMoneyThread(account, 1)
        threads.append(t)
        t.start()
        # 调用 start() 此时线程就处于就绪状态，未运行，未分配到时间片，一般先执行 start 再执行 join
        # 遇到 join 方法，则主线程阻塞，等待子线程结束，再执行 t.join() 后的代码块
    
    for t in threads:
        t.join()
    print("Account remain is %d." % account.balance)

if __name__ == "__main__":
    main()