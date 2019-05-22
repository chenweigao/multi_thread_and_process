from multiprocessing import Process
import os
import random
import time

def down_task(filename):
    print("starting downloading...pid is %d" % os.getpid())
    print("starting downloading file %s" % filename)
    time_to_download = random.randint(5, 10)
    time.sleep(time_to_download)
    print("Succed to download %s, cost %d seconds" % (filename, time_to_download))

def main():
    start = time.time()
    p1 = Process(target=down_task, args=('book1.txt',))
    p1.start()
    p2 = Process(target=down_task, args=('mp4.mp4',))
    p2.start()
    p1.join()
    p2.join()
    end = time.time()
    print("p1 + p2 costs %d seconds" % (end - start))
    
if __name__ == "__main__":
    main()