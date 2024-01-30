import argparse
import os
import stat
import subprocess
import sys
from pathlib import Path

def is_exe(fpath) -> bool:
    """Return true if fpath is a file we have access to that is executable."""
    accessmode = os.F_OK | os.X_OK
    if os.path.exists(fpath) and os.access(fpath, accessmode) and not os.path.isdir(fpath):
        filemode = os.stat(fpath).st_mode
        ret = bool(filemode & stat.S_IXUSR or filemode & stat.S_IXGRP or filemode & stat.S_IXOTH)
        return ret

def run_test(exec_path: Path, test_path: Path) -> str:
    """Run the test and return the output."""
    with open(test_path, 'r') as input_file:
        data = input_file.read()
    result = subprocess.run([exec_path], capture_output=True, text=True, input=data)
    return result.stdout

def check_test_result(golden_path: Path, test_result: str) -> tuple:
    """Check the test result against the golden file."""
    with open(golden_path, 'r') as golden_file:
        expected_result = golden_file.read()
    if test_result == expected_result:
        return True, "PASS"
    else:
        return False, f"-----\n{test_result}\nVS\n\n{expected_result}-----\n"

def find_tests_and_run(executable: Path, directory: Path) -> tuple:
    """Find and run tests recursively in the directory."""
    pass_count = fail_count = unsupported_count = 0 
    failed_tests = []
    unsupported_tests = []
    for test_file in directory.rglob('*.dat'):
        # Checking that the test file is not in the golden folder
        if not test_file.parts[-2] == "golden":
            # Path to golden file
            golden_file = test_file.parent / "golden" / test_file.with_suffix('.ans.dat').name
            relative_path = test_file.relative_to(directory)
            if golden_file.exists():
                test_result = run_test(executable, test_file)
                result_status, result_message = check_test_result(golden_file, test_result)
                if result_status:
                    pass_count += 1
                else:
                    fail_count += 1
                    failed_tests.append((relative_path, result_message))
            else:
                unsupported_count += 1
                unsupported_tests.append(relative_path)
    return pass_count, fail_count, unsupported_count, failed_tests, unsupported_tests

def generate_summary(pass_count: int, 
                     fail_count: int, 
                     unsupported_count: int,
                     failed_tests: list,
                     unsupported_tests: list,
                     verbose_flag: bool = False
                     ) -> str:
    """Generate summary of test results."""
    summary = ""
    if fail_count > 0:
        summary += "\nFailed tests:\n"
        for failed_test, message in failed_tests:
            summary += "\n" + str(failed_test) 
            if verbose_flag:
                summary += "\n" + message
        summary += "\n"
    if unsupported_count > 0:
        summary += "\nUnsupported goldens for:\n\n"
        for unsupported_test in unsupported_tests:
            summary += str(unsupported_test) + "\n" 
        summary += "\n"
    total_tests = pass_count + fail_count + unsupported_count
    summary += f"\nTotal tests count: {total_tests}\n"
    summary += f"PASS:              {pass_count}\n"
    summary += f"FAIL:              {fail_count}\n"
    summary += f"UNSUPPORTED:       {unsupported_count}"
    return summary

if __name__ == "__main__":
    parser = argparse.ArgumentParser()

    # Adding optional arguments
    parser.add_argument("-e", "--executable", required=True, help = "Executable main file which will be tested")
    parser.add_argument("-t", "--test_dir", required=True, help = "Directory containing tests (and golden dir with reference results)")
    parser.add_argument("-vv", "--VERBOSE", action="store_true", help="Enable verbose output for failed tests")

    # Read arguments from command line
    args = parser.parse_args()
    exec_path = Path(args.executable)
    test_root_dir = Path(args.test_dir)
    verbose_flag = args.VERBOSE

    if not is_exe(exec_path):
      print(f"{exec_path} is not an executable")
      sys.exit(1)

    if not test_root_dir.is_dir():
      print(f"{args.test_root_dir} is not a directory")
      sys.exit(1)

    # Print checked arguments
    print("Executable main file: % s" % exec_path)
    print("Directory containing tests: % s" % test_root_dir)
    
    test_runner = find_tests_and_run(exec_path, test_root_dir)
    summary = generate_summary(*test_runner, verbose_flag)
    print(summary)
