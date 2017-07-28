import filecmp
import os
import subprocess
from subprocess import Popen, PIPE

import time

COMP_BIN_PATH = '../TextMiningCompiler'
APP_BIN_PATH = '../TextMiningApp'

REF_COMP_BIN_PATH = '../ref/bin/linux64/TextMiningCompiler'
REF_APP_BIN_PATH = '../ref/bin/linux64/TextMiningApp'

DICT = '../ref/words.txt'
REF_DICT_BIN = '../ref/dict.bin'
DICT_BIN = 'dict.bin'

TESTS_DIR = './tests_files/'
TESTS_EXT = '.txt'
# TESTS_EXT = '100_0.txt'

LOG_FILE =  './logs.txt'
REF_LOG_FILE = './ref_logs.txt'
FNULL = open(os.devnull, 'w')


def okko(test):
    return '--> OK' if test else '--> KO'


def test_memory(process):
    ru = os.wait4(process.pid, 0)[2]

    if (ru.ru_maxrss / 1024) > 512:
        print(">> Maximum used memory: %d" % (ru.ru_maxrss / 1024), 'Mo', okko((ru.ru_maxrss / 1024) < 512))
    return ru.ru_maxrss / 1024

def test_comp():
    print('## COMPILER ##')
    start = time.time()
    p = Popen([COMP_BIN_PATH, DICT, DICT_BIN], stdout=PIPE, stderr=PIPE)
    test_memory(p)
    print(">> Took: " + str(round(time.time() - start, 3)) + "s")
    p = Popen([REF_COMP_BIN_PATH, DICT, REF_DICT_BIN], stdout=PIPE, stderr=PIPE)
    p.wait()



def search(filename, bin, dict_bin, log_file):
    with open(log_file, 'w+') as f:
        start = time.time()
        ps = subprocess.Popen(['cat', filename], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        ps2 = subprocess.Popen([bin, dict_bin], stdin=ps.stdout, stdout=f, stderr=FNULL)
        ps.wait()
        memUsed = test_memory(ps2)
        timeUsed = round(time.time() - start, 3)
        # _, err = ps.communicate()
        # output, _ = ps2.communicate()
        # if len(output) == 0:
        #     print('?? Warning: No output?')
        #     print("?? Cmd was: ", ' '.join(['cat', filename]), '|', ' '.join([bin, dict_bin]))

        # print(">> Took: " + str(timeUsed) + "s")
    return timeUsed, memUsed


def test_search():
    print('## SEARCH ##')

    #Stats
    totalTest, passedTest, memoryGoodTest = 0, 0, 0

    refTimeSum, mineTimeSum, diffTimeSum, percentTimeSum = 0, 0, 0, 0

    files = [TESTS_DIR + f for f in os.listdir(TESTS_DIR) if os.path.isfile(os.path.join(TESTS_DIR, f))]
    for filename in files:
        if filename[-len(TESTS_EXT):] != TESTS_EXT:
            continue
        totalTest += 1
        print('# File: ', filename)

        timeMine, memUsed = search(filename, APP_BIN_PATH, DICT_BIN, LOG_FILE)
        if memUsed < 512:
            memoryGoodTest += 1

        timeRef, _ = search(filename, REF_APP_BIN_PATH, REF_DICT_BIN, REF_LOG_FILE)

        filecmp.clear_cache()
        if not filecmp.cmp(LOG_FILE, REF_LOG_FILE):
            print('!! Diff with ref:')
            print('!!!!!!!!!!!!!!!!!!!!!!!Our!!!!!!!!!!!!!!!!!!!!!!!')
            with open(LOG_FILE, 'r') as f:
                print(f.read())
            print('!!!!!!!!!!!!!!!!!!!!!!!Ref!!!!!!!!!!!!!!!!!!!!!!!')
            with open(REF_LOG_FILE, 'r') as f:
                print(f.read())

        else:
            passedTest += 1
        refTimeSum += timeRef
        mineTimeSum += timeMine
        diffTimeSum += round(timeMine - timeRef, 3)
        percentTimeSum += round(timeMine / timeRef, 2)
        print('>> Time analysis: Ref', timeRef, 's | Ours', timeMine, 's | Difference',
              round(timeMine - timeRef, 3), 's | Ratio perf', round(timeMine / timeRef, 2))

    print('\n#########\n# RECAP #\n#########')
    print('>> Passed test:', passedTest, '/', totalTest, '(', 100 * passedTest // totalTest, '%)')
    print('>> Memory passed test:', memoryGoodTest, '/', totalTest, '(', 100 * memoryGoodTest // totalTest, '%)')
    print('>> Total Time analysis: Ref', round(refTimeSum, 3), 's | Ours',
          round(mineTimeSum, 3),
          's | Difference', round(diffTimeSum, 3), 's')
    print('>> Average Time analysis: Ref', round(refTimeSum / totalTest, 3), 's | Ours', round(mineTimeSum / totalTest, 3),
          's | Difference', round(diffTimeSum / totalTest, 3), 's | Ratio perf ', round(percentTimeSum / totalTest, 2))


if not os.path.isfile('./' + DICT_BIN):
    test_comp()
test_search()
