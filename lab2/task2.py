"""
    Basic thread handling exercise:

    Use the Thread class to create and run more than 10 threads which print their name and a random
    number they receive as argument. The number of threads must be received from the command line.

    e.g. Hello, I'm Thread-96 and I received the number 42

"""

import sys
from threading import Thread
import random

def hello_thread(id, number):
	print("Hello, I'm Thread-%d and I received the number %d" % (id, number))


if __name__ == "__main__":
	threadCount = int(sys.argv[1])

	threads = []

	for i in range(threadCount):
		threads.append(Thread(target = hello_thread, args = (i + 1, random.randint(0, 100))))


	for i in range(threadCount):
		threads[i].start()

	for i in range(threadCount):
		threads[i].join()
