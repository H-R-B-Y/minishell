#! /usr/bin/env python3

import json
import os
import sys
import subprocess

cases = "./cases/test_cases.json"

def compile_executable():
	subprocess.run(
		[
			"make",
			"--directory=../../",
			"MAIN=auto_test/fsm_tokeniser/test.c"
		]
	)
	subprocess.run(
		[
			"mv",
			"../../minishell",
			"./test"
		]
	)
	# Check if the compilation was successful
	if not os.path.isfile("./test"):
		print("Compilation failed. Exiting.")
		sys.exit(1)
	print("Compilation successful. Executable created at ./test")


def generate_golden_samples(executable = "./test"):

	# First check to see if golden samples exist, and double check that the user wants to overwrite them
	with open(cases, 'r') as f:
		test_cases = json.load(f)
	for case in test_cases:
		if "golden_sample" in case:
			if case["golden_sample"] is not None:
				response = input("Golden samples already exist. Do you want to overwrite them? (y/n): ")
				if response.lower() != 'y':
					print("Exiting without overwriting golden samples.")
					return
				break
	
	# Generate golden samples
	with open(cases, 'r') as f:
		test_cases = json.load(f)
	for case in test_cases["cases"]:
		body = case["body"]
		args = [executable]
		if isinstance(body, list):
			args.extend(body)
		else:
			args.append(body)

		result = subprocess.run(args, capture_output=True, text=True)
		output = result.stdout.strip()
		case["golden_sample"] = output
		print(f"Generated golden sample for case: {body}")
	with open(cases, 'w') as f:
		json.dump(test_cases, f, indent=4)


def main(executable = "./test"):

	with open(cases, 'r') as f:
		test_cases = json.load(f)
	
	count = 0
	passed = []
	failed = []

	for case in test_cases["cases"]:
		body = case["body"]
		golden = case["golden_sample"]

		args = [executable]
		if isinstance(body, list):
			args.extend(body)
		else:
			args.append(body)

		result = subprocess.run(args, capture_output=True, text=True)
		output = result.stdout.strip()
		if output == golden:
			passed.append(case)
		else:
			failed.append({
				"case": case,
				"output": output
			})
		count += 1
		print(f"Test case {count}: {'Passed' if output == golden else 'Failed'}")

	print(f"\nTotal test cases: {count}")
	print(f"Passed: {len(passed)}")
	print(f"Failed: {len(failed)}")
	print("pass percentage: {:.2f}%".format((len(passed) / count) * 100 if count > 0 else 0))


def cleanup(executable="./test"):
	if os.path.isfile(executable):
		subprocess.run(
			[
				"rm",
				executable
			]
		)


if __name__ == "__main__":
	import argparse

	parser = argparse.ArgumentParser(description="FSM Tokeniser Test Runner")
	parser.add_argument("--generate-golden-samples", action="store_true", help="Generate golden samples")
	parser.add_argument("--executable", type=str, default="./test", help="Path to the test executable")
	parser.add_argument("--cleanup", action="store_true", help="Cleanup the compiled executable after running tests")
	args = parser.parse_args()

	if not os.path.isfile(args.executable):
		print(f"Executable {args.executable} not found. Compiling...")
		compile_executable()
		args.executable = "./test"

	if args.generate_golden_samples:
		generate_golden_samples(executable=args.executable)
	else:
		main(executable=args.executable)
	
	if (args.cleanup):
		cleanup()