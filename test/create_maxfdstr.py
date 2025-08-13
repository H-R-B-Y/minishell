#!/usr/bin/python3

import sys, os

in_out = input("Input or Output (I/O): ")
in_out = 0 if in_out.lower()[0] == 'o' else 1 if in_out.lower()[0] == 'i' else None
if in_out == None:
	print("Not a valid type, must be I or O")
	sys.exit(1)

"""
file_path = "extra_data.json"
	if not os.path.exists(file_path):
		with open(file_path, "w") as f:
			json.dump({}, f)
	with open(file_path, "r") as f:
		try:
			data = json.load(f)
		except json.JSONDecodeError:
			data = {}
	data[key] = value
	with open(file_path, "w") as f:
		json.dump(data, f, indent=1)
	return True
"""

filename = input("File to open on maxfd")
if (not os.path.exists(filename)): # not a clean way to handle this
	file = open(filename, "w" if in_out == 0 else "r")
else:
	file = open(filename, "w" if in_out == 0 else "r")

maxfd = input("Maximum filedesc (int):")
maxfd = int(maxfd)
if (maxfd <= 0):
	print("invalid")
	sys.exit(1)

fdstr = f"{maxfd}{'<' if in_out == 0 else '>'} {filename}"
for i in list(range(maxfd))[::-1]:
	fdstr += f" {i}{'<' if in_out == 0 else '>'}&{i + 1}"

print(fdstr)