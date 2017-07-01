import os
import re


def get_file_size(path):
	return str(os.stat(path).st_size)


def get_number_of_operations():
	return int(tuple(open(r"number_of_operations.txt", 'r'))[0])


def spl(input):
	return re.split(r'[._]', input)


algos = ('haff', 'shan')
actions = ('-c', '-d')

f = open('info.csv', 'w')
header = 'name;old_size;new_size;operations;algo;action;size;set;num\n'
f.write(header)


files = os.listdir('sets')
for filename in files:
	str_to_write = ''
	# name
	str_to_write += filename + ';'
	path_in = (os.path.join('sets', filename))
	# old_size
	str_to_write += str(get_file_size(path_in)) + ';'
	beginning = str_to_write
	for algo in algos:
		# txt -> haff | shan
		path_out = path_in[:-3] + algo
		os.system('./a.out ' + algo + ' ' + '-c' + ' ' + path_in + ' ' + path_out)
		# new_size
		str_to_write += str(get_file_size(path_out)) + ';'
		# operations
		str_to_write += str(get_number_of_operations()) + ';'
		# algo
		str_to_write += algo + ';'
		# aciton
		str_to_write += 'c' + ';'
		# size
		str_to_write += spl(filename)[1] + ';'
		# set
		str_to_write += spl(filename)[2] + ';'
		# num
		str_to_write += spl(filename)[3] + '\n'
		f.write(str_to_write)
		str_to_write = beginning


files = os.listdir('sets')
archives_huff = []
archives_shan = []
for value in files:
	if 'haff' in value:
		archives_huff.append(value)

for value in files:
	if 'shan' in value:
		archives_shan.append(value)


for filename in archives_huff:
	str_to_write = ''
	# name
	str_to_write += filename + ';'
	path_in = (os.path.join('sets', filename))
	# haff | shan -> txt
	path_out = path_in[:-4] + '-unz-h.txt';
	# old_size
	str_to_write += str(get_file_size(path_in)) + ';'
	os.system('./a.out ' + 'haff' + ' -d ' + path_in + ' ' + path_out)
	# new_size
	str_to_write += str(get_file_size(path_out)) + ';'
	# operations
	str_to_write += str(get_number_of_operations()) + ';'
	# algo
	str_to_write += 'haff' + ';'
	# action
	str_to_write += 'd' + ';'
	# size
	str_to_write += spl(filename)[1] + ';'
	# set
	str_to_write += spl(filename)[2] + ';'
	# num
	str_to_write += spl(filename)[3] + '\n'
	f.write(str_to_write)


for filename in archives_shan:
	str_to_write = ''
	# name
	str_to_write += filename + ';'
	path_in = (os.path.join('sets', filename))
	# haff | shan -> txt
	path_out = path_in[:-4] + '-unz-s.txt';
	# old_size
	str_to_write += str(get_file_size(path_in)) + ';'
	os.system('./a.out ' + 'shan' + ' -d ' + path_in + ' ' + path_out)
	# new_size
	str_to_write += str(get_file_size(path_out)) + ';'
	# operations
	str_to_write += str(get_number_of_operations()) + ';'
	# algo
	str_to_write += 'shan' + ';'
	# action
	str_to_write += 'd' + ';'
	# size
	str_to_write += spl(filename)[1] + ';'
	# set
	str_to_write += spl(filename)[2] + ';'
	# num
	str_to_write += spl(filename)[3] + '\n'
	f.write(str_to_write)

f.close()
