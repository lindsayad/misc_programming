#!/usr/bin/python

decimal = raw_input('enter a number: ')
#output = bin(int(decimal))
output = "{0:b}".format(int(decimal))
print(output)
