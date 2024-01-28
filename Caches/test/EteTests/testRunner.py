import argparse
import os
import pathlib
import stat
import subprocess
import sys
from pathlib import Path

def is_exe(fpath):
    """Return true if fpath is a file we have access to that is executable."""
    accessmode = os.F_OK | os.X_OK
    if os.path.exists(fpath) and os.access(fpath, accessmode) and not os.path.isdir(fpath):
        filemode = os.stat(fpath).st_mode
        ret = bool(filemode & stat.S_IXUSR or filemode & stat.S_IXGRP or filemode & stat.S_IXOTH)
        return ret

def run_test(exec_file, test_path):
    """Run the test and return the output."""
    with open(test_path, 'r') as input_file:
        data = input_file.read()
    result = subprocess.run([exec_file], capture_output=True, text=True, input=data)
    return result.stdout

def findDiff(first, second):
    c = 0
    for ch in first:
        c ^= ord(ch)
    for ch in second:
        c ^= ord(ch)
    return chr(c)
 
def check_test_result(golden_path, test_result):
    """Check the test result against the golden file."""
    with open(golden_path, 'r') as golden_file:
        expected_result = golden_file.read()    
    if test_result == expected_result:
        return "PASS"
    else:
        return f"FAIL\n-----\n{test_result}\nVS\n\n{expected_result}-----\n"

def find_tests_and_run(executable, directory):
    """Find and run tests recursively in the directory."""
    for test_file in directory.rglob('*.dat'):
        # Checking that the test file is not in the golden folder
        if not test_file.parts[-2] == "golden":
            # Path to golden file
            golden_file = test_file.parent / "golden" / test_file.with_suffix('.ans.dat').name
            relative_path = test_file.relative_to(directory)
            if golden_file.exists():
                test_result = run_test(str(executable), str(test_file))
                check_result = check_test_result(str(golden_file), test_result)
                print(f"{relative_path}: {check_result}")
            else:
                print(f"Golden file for {relative_path} not found")

if __name__ == "__main__":
    parser = argparse.ArgumentParser()

    # Adding optional arguments
    parser.add_argument("-e", "--executable", required=True, help = "Executable main file which will be tested")
    parser.add_argument("-t", "--test_dir", required=True, help = "Directory containing tests (and golden dir with reference results)")

    # Read arguments from command line
    args = parser.parse_args()
    exec_path = Path(args.executable)
    test_root_dir = Path(args.test_dir)

    if not is_exe(exec_path):
      print(f"{exec_path} is not an executable")
      sys.exit(1)

    if not test_root_dir.is_dir():
      print(f"{args.test_root_dir} is not a directory")
      sys.exit(1)

    # Print checked arguments
    print("Executable main file: % s" % exec_path)
    print("Directory containing tests: % s" % test_root_dir)

    find_tests_and_run(exec_path, test_root_dir)
