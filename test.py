#! /usr/bin/python3

import os

if "luna" in os.environ.keys():
	print(f"{os.environ['luna']}")