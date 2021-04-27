#!/bin/python3

import sys

if len(sys.argv) != 2:
    print("Usage: fib_hex_print.py [number]")
    sys.exit()

x1 = 0
x2 = 0
x3 = 1

for i in range(0, int(sys.argv[1], 0)):
    x1 = x2
    x2 = x3
    x3 = x2 + x1
    print("%x:\t%x"%(i + 1, x3))
