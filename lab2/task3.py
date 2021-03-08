"""
Coffee Factory: A multiple producer - multiple consumer approach

Generate a base class Coffee which knows only the coffee name
Create the Espresso, Americano and Cappuccino classes which inherit the base class knowing that
each coffee type has a predetermined size.
Each of these classes have a get message method

Create 3 additional classes as following:
    * Distributor - A shared space where the producers puts coffees and the consumers takes them
    * CoffeeFactory - An infinite loop, which always sends coffees to the distributor
    * User - Another infinite loop, which always takes coffees from the distributor

The scope of this exercise is to correctly use threads, classes and synchronization objects.
The size of the coffee (ex. small, medium, large) is chosen randomly everytime.
The coffee type is chosen randomly everytime.

Example of output:

Consumer 65 consumed espresso
Factory 7 produced a nice small espresso
Consumer 87 consumed cappuccino
Factory 9 produced an italian medium cappuccino
Consumer 90 consumed americano
Consumer 84 consumed espresso
Factory 8 produced a strong medium americano
Consumer 135 consumed cappuccino
Consumer 94 consumed americano
"""
import random
import threading
from collections import deque

class Coffee:
    """ Base class """
    def __init__(self):
        pass

    def get_name(self):
        """ Returns the coffee name """
        raise NotImplementedError

    def get_size(self):
        """ Returns the coffee size """
        raise NotImplementedError

class Espresso(Coffee):
    def __init__(self, size):
        self.name = "Espresso"
        self.size = size

    def get_name(self):
        return self.name

    def get_size(self):
        return self.size

    def get_message(self):
        if self.size == 0:
            return "small sized " + self.name
        elif self.size == 1:
            return "medium sized " + self.name
        elif self.size == 2:
            return "large sized " + self.name

class Americano(Coffee):
    def __init__(self, size):
        self.name = "Americano"
        self.size = size

    def get_name(self):
        return self.name

    def get_size(self):
        return self.size

    def get_message(self):
        if self.size == 0:
            return "small sized " + self.name
        elif self.size == 1:
            return "medium sized " + self.name
        elif self.size == 2:
            return "large sized " + self.name

class Cappuccino(Coffee):
    def __init__(self, size):
        self.name = "Cappuccino"
        self.size = size

    def get_name(self):
        return self.name

    def get_size(self):
        return self.size

    def get_message(self):
        if self.size == 0:
            return "small sized " + self.name
        elif self.size == 1:
            return "medium sized " + self.name
        elif self.size == 2:
            return "large sized " + self.name


# CoffeeFactory (producer)
class CoffeeFactory(threading.Thread):

    def __init__(self, distributor, id, cond):
        threading.Thread.__init__(self)
        self.distributor = distributor
        self.id = id
        self.cond = cond

    def run(self):
        while(True):
            # generare random cafea
            coffeeType = random.randint(0, 2)
            size = random.randint(0, 2)

            coffee = None

            if coffeeType == 0:
                coffee = Espresso(size)
            elif coffeeType == 1:
                coffee = Americano(size)
            elif coffeeType == 2:
                coffee = Cappuccino(size)

            # producere cafea
            with self.cond:
                if self.distributor.isEmpty():
                    self.distributor.put(coffee)
                    self.cond.notify()
                else:
                    while self.distributor.isFull():
                        self.cond.wait()
                    self.distributor.put(coffee)

            print("Factory " + str(self.id) + " produced a " + coffee.get_message())

# Distributor (Buffer)
class Distributor:
    def __init__(self, maxSize):
        self.distributor = deque()
        self.maxSize = maxSize

    # conditii pentru buffer gol si plin
    def isEmpty(self):
        return len(self.distributor) == 0

    def isFull(self):
        return len(self.distributor) == self.maxSize

    
    # metodele put si get
    def put(self, coffee):
        self.distributor.appendleft(coffee)
        self.maxSize += 1

    def get(self):
        return self.distributor.pop()
        self.maxSize -= 1

# User (consumer)
class User(threading.Thread):
    def __init__(self, distributor, id, cond):
        threading.Thread.__init__(self)
        self.distributor = distributor
        self.id = id
        self.cond = cond

    def run(self):
        while(True):
            # consumare cafea
            with self.cond:
                if self.distributor.isFull():
                    coffee = self.distributor.get()
                    self.cond.notify()
                else:
                    while self.distributor.isEmpty():
                        self.cond.wait()
                    coffee = self.distributor.get()
            print("Consumer " + str(self.id) + " consumed " + coffee.get_name())

if __name__ == '__main__':

    # citire parametrii
    producers_count = int(input("Enter producer count: "))
    consumers_count = int(input("Enter consumer count: "))

    cond = threading.Condition()

    distributor = Distributor(10)

    factories = []
    consumers = []

    # creare liste de thread-uri
    for i in range(producers_count):
        factories.append(CoffeeFactory(distributor, i + 1, cond))
    for i in range(consumers_count):
        consumers.append(User(distributor, i + 1, cond))

    # start si join
    for i in range(producers_count):
        factories[i].start()
    for i in range(consumers_count):
        consumers[i].start()

    for i in range(producers_count):
        factories[i].join()
    for i in range(consumers_count):
        consumers[i].join()
