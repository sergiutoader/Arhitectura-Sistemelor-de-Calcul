"""
This module offers the available Products.

Computer Systems Architecture Course
Assignment 1
March 2021
"""

from dataclasses import dataclass


@dataclass(init=True, repr=True, order=False, frozen=True)
class Product:
    """
    Class that represents a product.
    """
    name: str
    price: int

    # equality check function for Product objects
    def __eq__(self, other):
        if (isinstance(self, Tea) and isinstance(other, Coffee)) or \
            (isinstance(self, Coffee) and isinstance(self, Tea)):
            return False
        return self.name == other.name and self.price == other.price


@dataclass(init=True, repr=True, order=False, frozen=True)
class Tea(Product):
    """
    Tea products
    """
    type: str


@dataclass(init=True, repr=True, order=False, frozen=True)
class Coffee(Product):
    """
    Coffee products
    """
    acidity: str
    roast_level: str
