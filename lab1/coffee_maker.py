"""
A command-line controlled coffee maker.
"""

import sys
from load_recipes import load_recipes

"""
Implement the coffee maker's commands. Interact with the user via stdin and print to stdout.

Requirements:
    - use functions
    - use __main__ code block
    - access and modify dicts and/or lists
    - use at least once some string formatting (e.g. functions such as strip(), lower(),
    format()) and types of printing (e.g. "%s %s" % tuple(["a", "b"]) prints "a b"
    - BONUS: read the coffee recipes from a file, put the file-handling code in another module
    and import it (see the recipes/ folder)

There's a section in the lab with syntax and examples for each requirement.

Feel free to define more commands, other coffee types, more resources if you'd like and have time.
"""

"""
Tips:
*  Start by showing a message to the user to enter a command, remove our initial messages
*  Keep types of available coffees in a data structure such as a list or dict
e.g. a dict with coffee name as a key and another dict with resource mappings (resource:percent)
as value
"""

# Commands
EXIT = "exit"
LIST_COFFEES = "list"
MAKE_COFFEE = "make"  #!!! when making coffee you must first check that you have enough resources!
HELP = "help"
REFILL = "refill"
RESOURCE_STATUS = "status"
commands = [EXIT, LIST_COFFEES, MAKE_COFFEE, REFILL, RESOURCE_STATUS, HELP]

# Coffee examples
ESPRESSO = "espresso"
AMERICANO = "americano"
CAPPUCCINO = "cappuccino"

# Resources examples
WATER = "water"
COFFEE = "coffee"
MILK = "milk"

# Coffee maker's resources - the values represent the fill percents
RESOURCES = {WATER: 100, COFFEE: 100, MILK: 100}

RECIPES = load_recipes()

"""
Example result/interactions:

I'm a smart coffee maker
Enter command:
list
americano, cappuccino, espresso
Enter command:
status
water: 100%
coffee: 100%
milk: 100%
Enter command:
make
Which coffee?
espresso
Here's your espresso!
Enter command:
refill
Which resource? Type 'all' for refilling everything
water
water: 100%
coffee: 90%
milk: 100%
Enter command:
exit
"""

def list_coffees():
	print("%s, %s, %s" % (ESPRESSO, AMERICANO, CAPPUCCINO))

def resource_status():
	print("%s: %d%%" % (WATER, RESOURCES[WATER]))
	print("%s: %d%%" % (COFFEE, RESOURCES[COFFEE]))
	print("%s: %d%%" % (MILK, RESOURCES[MILK]))

def get_recipe(coffee_type):
	return RECIPES[coffee_type]

def get_coffee_type():
	print("Which coffee?")
	return sys.stdin.readline().strip()

def make(coffee_type):
	try:
		RECIPE = RECIPES[coffee_type]
	except KeyError as e:
		print("Invalid coffee name")
		return

	new_water_val = RESOURCES[WATER] - RECIPE[WATER]
	new_coffee_val = RESOURCES[COFFEE] - RECIPE[COFFEE]
	new_milk_val = RESOURCES[MILK] - RECIPE[MILK]

	if new_water_val < 0 or new_coffee_val < 0 or new_milk_val < 0:
		print("Not enough resources to make ",  coffee_type)
		return

	RESOURCES[WATER] = new_water_val
	RESOURCES[COFFEE] = new_coffee_val
	RESOURCES[MILK] = new_milk_val

	print("Here's your %s!" % (coffee_type))

def get_resource_type():
	print("Which resource? Type 'all' for refilling everything")
	return sys.stdin.readline().strip()

def refill(resource_type):
	if resource_type == "all":
		RESOURCES[WATER] = 100
		RESOURCES[COFFEE] = 100
		RESOURCES[MILK] = 100
	elif resource_type == WATER:
		RESOURCES[WATER] = 100
	elif resource_type == MILK:
		RESOURCES[MILK] = 100
	elif resource_type == COFFEE:
		RESOURCES[COFFEE] = 100	


def help():
	print("List of possible commands:")
	for command in commands:
		print(command)

if __name__ == "__main__":
	command = ""
	print("I'm a smart coffee maker")
	while not command == EXIT:

		print("Enter command:")
		command = sys.stdin.readline().strip()

		if command == LIST_COFFEES:
			list_coffees()
		elif command == RESOURCE_STATUS:
			resource_status()
		elif command == MAKE_COFFEE:
			coffee_type = get_coffee_type()
			make(coffee_type)
		elif command == REFILL:
			resource_type = get_resource_type()
			refill(resource_type)
			resource_status()
		elif command == HELP:
			help()

