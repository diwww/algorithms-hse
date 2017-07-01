import string
import random
import os


def generate(file_name, set_type, min_size):
    f = open(file_name, 'w')
    while os.stat(file_name).st_size < min_size:
        f.write(random.choice(set_type))
    f.close()


def cut(s):
    if s >= 1000000:
        return s // 1000000
    else:
        return s // 1000


russian_string = u'йцукенгшщзхъфывапролджэячсмитьбю'
russian_string += russian_string.upper()

set_1 = list(string.ascii_letters) + [' ', '\n']
set_2 = [x for x in russian_string] + set_1
set_3 = set_2 + list(string.punctuation)

# sizes = [20000, 40000, 60000, 80000, 100000, 1000000, 2000000, 3000000]
sizes = [60000,61000,62000,63000,64000,65000]
# sets = [set_1, set_2, set_3]
sets = [set_2]

if not os.path.exists('sets'):
    os.makedirs('sets')

for s in sizes:
    for t in range(0, len(sets)):
        generate(r'sets/set_' + str(cut(s)) + '_' + str(t + 2) + '_1.txt', sets[t], s)
        generate(r'sets/set_' + str(cut(s)) + '_' + str(t + 2) + '_2.txt', sets[t], s)
        generate(r'sets/set_' + str(cut(s)) + '_' + str(t + 2) + '_3.txt', sets[t], s)
