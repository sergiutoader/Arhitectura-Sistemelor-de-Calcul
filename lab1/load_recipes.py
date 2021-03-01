"""
	Bonus task: load all the available coffee recipes from the folder 'recipes/'
	File format:
		first line: coffee name
		next lines: resource=percentage

	info and examples for handling files:
		http://cs.curs.pub.ro/wiki/asc/asc:lab1:index#operatii_cu_fisiere
		https://docs.python.org/3/library/io.html
		https://docs.python.org/3/library/os.path.html
"""

RECIPES_FOLDER = "recipes"

def parse_file(filename):
	ingredients = {}
	with open(RECIPES_FOLDER + "/" + filename, "r") as f:
		resource_type = f.readline().strip()

		for i in range(3):
			line = f.readline().strip().split("=")
			ingredients[line[0]] = int(line[1])

	return ingredients

def load_recipes():
	recipes = {}

	recipes["americano"] = parse_file("americano.txt")
	recipes["cappuccino"] = parse_file("cappuccino.txt")
	recipes["espresso"] = parse_file("espresso.txt")

	return recipes