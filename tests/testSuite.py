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

TEST_FILE = 'test.txt'

FNULL = open(os.devnull, 'w')



def test_comp():
    print('## COMPILER ##')
    start = time.time()
    p = Popen(['/usr/bin/time', '-v', COMP_BIN_PATH, DICT, DICT_BIN],  # ['/usr/bin/time', '-v', 'ls'],
                           stdout=PIPE, stderr=PIPE)
    p.wait()
    print(">> Took: " + str(round(time.time() - start, 3)) + "s")
    output, err = p.communicate()
    memSize = int(err.decode('utf-8').split('\n')[-15].split(' ')[-1])
    print(">> Maximum used memory (Mo): ", memSize // 1024)


def test_search():
    print('## SEARCH ##')
    start = time.time()
    files = ['./tests_files/' + f for f in os.listdir('./tests_files') if os.path.isfile(os.path.join('./tests_files', f))]
    for filename in files:
        if filename[-4:] != '.txt':
            continue
        print('# File: ', filename)

        ps = subprocess.Popen(['cat', filename], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        output = subprocess.check_output([APP_BIN_PATH, DICT_BIN], stdin=ps.stdout)
        ps.wait()
        _, err = ps.communicate()
        print(output, err)
        mine = output.decode('utf-8')
        # memSize = int(err.decode('utf-8').split('\n')[-15].split(' ')[-1])
        # print(">> Maximum used memory (Mo): ", memSize // 1024)


        ps = subprocess.Popen(['cat', filename], stdout=subprocess.PIPE, stderr=FNULL)
        output = subprocess.check_output([REF_APP_BIN_PATH, REF_DICT_BIN], stdin=ps.stdout, stderr=FNULL)
        ps.wait()
        ref = output.decode('utf-8')
        # print(ref)
        # print(mine)
        print('>> Diff with ref: ', 'KO' if mine != ref else 'OK')



# test_comp()
test_search()