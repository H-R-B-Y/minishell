#! /usr/bin/python3

import subprocess
import json
import os, sys

def split_to_err(error_line):
	seps = error_line.split(":")
	row = seps[2].split(',')[0].strip()
	col = seps[3].strip().split(')')[0]
	err = seps[4].strip()
	return row, col, err

def run_norminette(file_path, *args, **kwargs):
	proc = subprocess.run(["norminette", file_path], text=True, capture_output=True)
	lines = proc.stdout.splitlines()
	if len(lines) > 1:
		for line in lines[1:]:
			if (line.split(" ")[0] != "Error:"):
				continue
			line, col, err = split_to_err(line)
			print(f"{file_path}:{line}:{col}: {err}")
		print("")
	else:
		pass

def collect_file_paths(root):
	out = []
	for entry in os.listdir(root):
		if (entry[0] != '.'):
			full_path = os.path.join(root, entry)
			out.append(full_path)
	return out

def print_norm_errors(root):
	if os.path.isfile(root):
		run_norminette(root);
	elif os.path.isdir(root):
		files = collect_file_paths(root)
		for file in files:
			print_norm_errors(file)
	else:
		print(f"argument {root} is not a file or directory")

def main():
	args = sys.argv[1:]
	for arg in args:
		try:
			print_norm_errors(arg)
		except Exception as e:
			filename = getattr(e, 'filename', None)
			lineno = getattr(e, 'lineno', None)
			offset = getattr(e, 'offset', None)
			msg = getattr(e, 'msg', str(e))
			print(f"{filename}:{lineno}:{offset}: {msg}")


if __name__ == "__main__":
	main()