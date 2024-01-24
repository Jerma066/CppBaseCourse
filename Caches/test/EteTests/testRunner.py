import argparse
import os
import pathlib
import stat
import subprocess
import sys

def isExe(fpath):
    """ Return true if fpath is a file we have access to that is executable """
    accessmode = os.F_OK | os.X_OK
    if os.path.exists(fpath) and os.access(fpath, accessmode) and not os.path.isdir(fpath):
        filemode = os.stat(fpath).st_mode
        ret = bool(filemode & stat.S_IXUSR or filemode & stat.S_IXGRP or filemode & stat.S_IXOTH)
        return ret

def runTest(execFile, testPath):
    with open(test_path, 'r') as input_file:
        data = input_file.read()
    result = subprocess.run([execFile], capture_output=True, text=True, input=data)
    return result.stdout

def findDiff(first, second):
    c = 0
    for ch in first:
        c ^= ord(ch)
    for ch in second:
        c ^= ord(ch)
    return chr(c)
 
def chechTestResult(goldenPath, testResult):
    goldenFile = open(goldenPath, 'r')
    expectedResult = "".join(goldenFile.readlines())
    goldenFile.close()
    checkStatus = "FAIL"
    if testResult == expectedResult:
      checkStatus = "PASS"
    else:
      checkStatus += "\n-----\n" + testResult + "\nVS\n\n" + expectedResult + "-----" + '\n'
    return checkStatus
    

if __name__ == "__main__":
    parser = argparse.ArgumentParser()

    # Adding optional arguments
    parser.add_argument("-e", "--executable", required=True, help = "Executable main file which will be tested")
    parser.add_argument("-t", "--test_dir", required=True, help = "Directory containing tests (and golden dir with reference results)")

    # Read arguments from command line
    args = parser.parse_args()
    if not isExe(args.executable):
      print(f"{args.executable} is not an executable")
      sys.exit(1)

    testDir = pathlib.Path(args.test_dir)
    if not testDir.is_dir():
      print(f"{args.test_dir} is not a directory")
      sys.exit(1)

    # Print checked arguments
    print("Executable main file: % s" % args.executable)
    print("Directory containing tests: % s" % args.test_dir)

    test_files = [f for f in os.listdir(args.test_dir) if f.endswith('.dat') and not f.startswith('golden')]

    for test_file in test_files:
        test_path = os.path.join(args.test_dir, test_file)
        golden_path = os.path.join(args.test_dir, "golden", test_file.replace('.dat', '.ans.dat'))

        if os.path.exists(golden_path):
            testResult = runTest(args.executable, test_path)
            checkResult = chechTestResult(golden_path, testResult)
            print(checkResult)
        else:
            print(f"Golden file for {test_file} not found")
