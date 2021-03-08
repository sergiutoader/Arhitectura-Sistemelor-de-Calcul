from threading import Thread, RLock
import time

class Philosopher(Thread):
    def __init__(self, id, leftFork, rightFork):
        Thread.__init__(self)
        self.id = id
        self.leftFork = leftFork
        self.rightFork = rightFork

        # interschimbare furculite pentru primul filozof
        if self.id == 0:
            self.leftFork, self.rightFork = self.rightFork, self.leftFork

    # asteapta o secunda
    def think(self):
        time.sleep(1)
        print("Philosopher " + str(self.id) + " is thinking for 1 second...")

    def run(self):
        self.leftFork.acquire()
        self.rightFork.acquire()

        self.think()

        self.leftFork.release()
        self.rightFork.release()

if __name__ == "__main__":
    N = int(input("Enter Philosopher count: "))

    philosophers = []
    forks = []
    
    for i in range(N):
        forks.append(RLock())
    # creare liste de thread-uri
    for i in range(N):
        philosophers.append(Philosopher(i + 1, forks[i], forks[(i + 1) % N]))
    
    for i in range(N):
        philosophers[i].start()

    for i in range(N):
        philosophers[i].join()