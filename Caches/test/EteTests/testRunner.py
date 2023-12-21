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
    inputFile = open(testPath, 'r')
    data = "".join(inputFile.readlines())
    inputFile.close() 
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

    testResult = runTest(args.executable, args.test_dir + "test1.dat")
    checkResult = chechTestResult(args.test_dir + "golden/test1.ans.dat", testResult)
    print(checkResult)

    testResult = runTest(args.executable, args.test_dir + "test2.dat")
    checkResult = chechTestResult(args.test_dir + "golden/test2.ans.dat", testResult)
    print(checkResult)


    testResult = runTest(args.executable, args.test_dir + "test3.dat")
    checkResult = chechTestResult(args.test_dir + "golden/test3.ans.dat", testResult)
    print(checkResult)

    testResult = runTest(args.executable, args.test_dir + "test4.dat")
    checkResult = chechTestResult(args.test_dir + "golden/test4.ans.dat", testResult)
    print(checkResult)

    testResult = runTest(args.executable, args.test_dir + "test5.dat")
    checkResult = chechTestResult(args.test_dir + "golden/test5.ans.dat", testResult)
    print(checkResult)

    testResult = runTest(args.executable, args.test_dir + "test6.dat")
    checkResult = chechTestResult(args.test_dir + "golden/test6.ans.dat", testResult)
    print(checkResult)

    testResult = runTest(args.executable, args.test_dir + "test7.dat")
    checkResult = chechTestResult(args.test_dir + "golden/test7.ans.dat", testResult)
    print(checkResult)

    testResult = runTest(args.executable, args.test_dir + "test8.dat")
    checkResult = chechTestResult(args.test_dir + "golden/test8.ans.dat", testResult)
    print(checkResult)

    testResult = runTest(args.executable, args.test_dir + "test9.dat")
    checkResult = chechTestResult(args.test_dir + "golden/test9.ans.dat", testResult)
    print(checkResult)

    testResult = runTest(args.executable, args.test_dir + "test10.dat")
    checkResult = chechTestResult(args.test_dir + "golden/test10.ans.dat", testResult)
    print(checkResult)

    testResult = runTest(args.executable, args.test_dir + "test11.dat")
    checkResult = chechTestResult(args.test_dir + "golden/test11.ans.dat", testResult)
    print(checkResult)

    testResult = runTest(args.executable, args.test_dir + "test12.dat")
    checkResult = chechTestResult(args.test_dir + "golden/test12.ans.dat", testResult)
    print(checkResult)

    testResult = runTest(args.executable, args.test_dir + "test13.dat")
    checkResult = chechTestResult(args.test_dir + "golden/test13.ans.dat", testResult)
    print(checkResult)

    testResult = runTest(args.executable, args.test_dir + "test14.dat")
    checkResult = chechTestResult(args.test_dir + "golden/test14.ans.dat", testResult)
    print(checkResult)


    testResult = runTest(args.executable, args.test_dir + "test15.dat")
    checkResult = chechTestResult(args.test_dir + "golden/test15.ans.dat", testResult)
    print(checkResult)


    testResult = runTest(args.executable, args.test_dir + "test16.dat")
    checkResult = chechTestResult(args.test_dir + "golden/test16.ans.dat", testResult)
    print(checkResult)

    testResult = runTest(args.executable, args.test_dir + "vki_005.dat")
    checkResult = chechTestResult(args.test_dir + "golden/vki_005.ans.dat", testResult)
    print(checkResult)

    testResult = runTest(args.executable, args.test_dir + "vki_20-500.dat")
    checkResult = chechTestResult(args.test_dir + "golden/vki_20-500.ans.dat", testResult)
    print(checkResult)

    testResult = runTest(args.executable, args.test_dir + "vki_011.dat")
    checkResult = chechTestResult(args.test_dir + "golden/vki_011.ans.dat", testResult)
    print(checkResult)
