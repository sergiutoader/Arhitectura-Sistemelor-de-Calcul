"""
This module represents the Marketplace.

Computer Systems Architecture Course
Assignment 1
March 2021
"""

import threading

class ReservedProduct:
    """ class that stores a product and a boolean value
    for the reserved status of that product """

    def __init__(self, product):
        self.product = product
        self.reserved = False

    def set_reserved(self):
        """ Sets reserved value on True """
        self.reserved = True

    def set_unreserved(self):
        """ Sets reserved value on False """
        self.reserved = False

    def is_reserved(self):
        """ Returns value of reserved field """
        return self.reserved


class Cart:
    """ Class that represents a shopping cart
        contains a queue object and append and remove operations """
    def __init__(self):
        self.queue = []

    def append(self, product):
        """ Appends product to cart's list """
        self.queue.append(product)

    def remove(self, product):
        """ Searches for the product and removes it from the queue """
        for item in self.queue:
            if item == product:
                self.queue.remove(item)
                return

class ProducerQueue:
    """
        Class that represents a queue for each producer's products #
        It keeps track of product's reserved status and the queue's ammount of
            products compared to it's maximum capacity #
        Performs synchronized append and remove #
    """
    def __init__(self, queue_size, lock):
        self.lock = lock
        self.queue_size = queue_size
        self.curr_size = 0
        self.queue = []

    def append(self, product):
        """ Attempts to add product to queue
            Returns False if queue is full, otherwise it returns true and
            increments current size field """
        with self.lock:
            if self.is_full():
                return False
            self.queue.append(product)
            self.curr_size += 1
            return True

    def remove(self, product):
        """ Removes product from field and decrements current size field """
        with self.lock:
            self.queue.remove(product)
            self.curr_size -= 1

    def is_full(self):
        """ Function that checks whether queue has reached maximum capacity """
        return self.queue_size <= self.curr_size

class Marketplace:
    """
    Class that represents the Marketplace. It's the central part of the implementation.
    The producers and consumers use its methods concurrently.
    """
    def __init__(self, queue_size_per_producer):
        """
        Constructor

        :type queue_size_per_producer: Int
        :param queue_size_per_producer: the maximum size of a queue associated with each producer
        """

        # condition object used for synchronization
        self.lock = threading.Condition()

        # unique id for each producer
        self.producer_id = 0
        # set that stores ProducerQueue objects
        self.producers = {}

        # unique id for each cart
        self.cart_id = 0

        # set that stores Cart objects
        self.carts = {}

        # maximum queue size
        self.queue_size = queue_size_per_producer


    def register_producer(self):
        """
        Returns an id for the producer that calls this.
        Method that incrementally generates a new id for each producer and
        adds a new ProducerQueue object in the producers set.
        """
        with self.lock:
            self.producer_id += 1
            self.producers[self.producer_id] = ProducerQueue(self.queue_size, self.lock)
            return self.producer_id

    def publish(self, producer_id, product):
        """
        Adds the product provided by the producer to the marketplace

        :type producer_id: String
        :param producer_id: producer id

        :type product: Product
        :param product: the Product that will be published in the Marketplace

        :returns True or False. If the caller receives False, it should wait and then try again.

        Method that adds product to the queue of the producer who created it
        """
        queue = self.producers[producer_id]
        succeeded = queue.append(ReservedProduct(product))
        return succeeded

    def new_cart(self):
        """
        Creates a new cart for the consumer

        :returns an int representing the cart_id

        Method that incrementally generates a new id for each cart and adds
        a new Cart object to the carts set
        """
        with self.lock:
            self.cart_id += 1
            self.carts[self.cart_id] = Cart()
            return self.cart_id

    def add_to_cart(self, cart_id, product):
        """
        Adds a product to the given cart. The method returns

        :type cart_id: Int
        :param cart_id: id cart

        :type product: Product
        :param product: the product to add to cart

        :returns True or False. If the caller receives False, it should wait and then try again

        Method that adds product to the requested cart
        It searches for the product in all the queues and marks it as reserved
        """

        for producer in self.producers.values():
            for prod in producer.queue:
                if product == prod.product and not prod.is_reserved():
                    self.carts[cart_id].append(product)
                    prod.set_reserved()
                    return True
        return False

    def remove_from_cart(self, cart_id, product):
        """
        Removes a product from cart.

        :type cart_id: Int
        :param cart_id: id cart

        :type product: Product
        :param product: the product to remove from cart

        Method that removes a product from the requested cart
        It searches for the product in all the queues and marks it as unreserved
        """

        self.carts[cart_id].remove(product)
        with self.lock:
            for producer in self.producers.values():
                for prod in producer.queue:
                    if product == prod.product and prod.is_reserved():
                        prod.set_unreserved()
                        return

    def place_order(self, cart_id):
        """
        Return a list with all the products in the cart.

        :type cart_id: Int
        :param cart_id: id cart

        Returns all the items in the cart as a list
        Searches for each product in all queues and removes it
        """

        with self.lock:
            for bought_product in self.carts[cart_id].queue:
                for producer in self.producers.values():
                    for res_product in producer.queue:
                        if bought_product == res_product.product:
                            producer.remove(res_product)

            return list(self.carts[cart_id].queue)
