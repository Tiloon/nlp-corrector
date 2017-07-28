from random import randrange, sample

DICT = '../ref/words.txt'
TESTS_DIR = './tests_files/'

def createTest(fileName, nbWord, approx, lines):
    linesPicked = sample(range(0, 100000), nbWord)
    words = [lines[i].split('\t')[0] for i in linesPicked]
    with open(TESTS_DIR + fileName, 'w+') as f:
        for w in words:
            f.write('approx ' + str(approx) + ' ' + w + '\n')


with open(DICT) as f:
    lines = f.readlines()
    for approx in range(0, 3):
        for nb in [10, 30, 100, 300, 1000, 3000]:
            print('rand_' + str(nb) + '_' + str(approx) + '.txt')
            createTest('rand_' + str(nb) + '_' + str(approx) + '.txt', nb, approx, lines)
