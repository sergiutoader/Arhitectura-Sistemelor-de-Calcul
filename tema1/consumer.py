"""
This module represents the Consumer.

Computer Systems Architecture Course
Assignment 1
March 2021
"""

from threading import Thread
from time import sleep


class Consumer(Thread):
    """
    Class that represents a consumer.
    """

    def __init__(self, carts, marketplace, retry_wait_time, **kwargs):
        """
        Constructor.

        :type carts: List
        :param carts: a list of add and remove operations

        :type marketplace: Marketplace
        :param marketplace: a reference to the marketplace

        :type retry_wait_time: Time
        :param retry_wait_time: the number of seconds that a producer must wait
        until the Marketplace becomes available

        :type kwargs:
        :param kwargs: other arguments that are passed to the Thread's __init__()
        """
        Thread.__init__(self)

        # carts is a list of carts, each cart is a list
        # of operations made on a product
        self.carts = carts

        # marketplace object
        self.marketplace = marketplace

        # retry wait time
        self.retry_wait_time = retry_wait_time

        # name of the consumer
        self.name = kwargs['name']

    def cart_operations(self, cart):
        """ Applies all operations for a given cart """
        # create new cart object
        cart_id = self.marketplace.new_cart()

        # extract type, product, quantity from each operation in cart
        for operation in cart:
            op_type = operation['type']
            op_product = operation['product']
            op_quantity = operation['quantity']

            while op_quantity > 0:
                # add each item individually to cart if possible,
                # otherwise wait and retry
                if op_type == 'add':
                    while True:
                        added = self.marketplace.add_to_cart( \
                            cart_id, op_product)
                        if not added:
                            sleep(self.retry_wait_time)
                        else:
                            break
                    op_quantity -= 1
                # remove each item individually from the cart
                if op_type == 'remove':
                    self.marketplace.remove_from_cart(cart_id, op_product)
                    op_quantity -= 1
        # place order after all cart operations have been processed
        products = self.marketplace.place_order(cart_id)
        # print output
        for prod in products:
            print(self.name, 'bought', prod)

    def run(self):

        # build each cart in order
        for cart in self.carts:
            self.cart_operations(cart)
            