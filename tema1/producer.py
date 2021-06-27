"""
This module represents the Producer.

Computer Systems Architecture Course
Assignment 1
March 2021
"""

from threading import Thread
from time import sleep

class Producer(Thread):
    """
    Class that represents a producer.
    """

    def __init__(self, products, marketplace, republish_wait_time, **kwargs):
        """
        Constructor.

        @type products: List()
        @param products: a list of products that the producer will produce

        @type marketplace: Marketplace
        @param marketplace: a reference to the marketplace

        @type republish_wait_time: Time
        @param republish_wait_time: the number of seconds that a producer must
        wait until the marketplace becomes available

        @type kwargs:
        @param kwargs: other arguments that are passed to the Thread's __init__()
        """

        Thread.__init__(self, daemon=True)

        # List of produced Coffee and Tea, with respective quantity and wait_time
        self.products = products

        # Marketplace object
        self.marketplace = marketplace

        # time to wait before republishing
        self.republish_wait_time = republish_wait_time

        # producer name
        self.name = kwargs['name']

        # register producer to marketplace
        self.producer_id = self.marketplace.register_producer()


    def run(self):
        # Producer continously publishes products to marketplace
        while True:
            # extract product, quantity and wait time info from products object
            for item in self.products:
                product = item[0]
                quantity = item[1]
                wait_time = item[2]

                # individually publish each item
                # if not successful, retry after wait time
                while quantity > 0:
                    while True:
                        published = self.marketplace.publish( \
                            self.producer_id, product)
                        if not published:
                            sleep(self.republish_wait_time)
                        else:
                            break
                    # upon publishing, wait specified time
                    # until next item can be published
                    sleep(wait_time)
                    quantity -= 1
