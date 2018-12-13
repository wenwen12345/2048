# coding=UTF-8

'''
    2048
    ====
        Game 2048.
'''

# Import Python Lib
import numpy as np
import random
import sys
import msvcrt
import os

################################################################################
# Game Class
################################################################################

class Game:

    def __init__(self):

        self.__gameMap = np.zeros((4, 4), dtype = int)
        self.createNewNum()
        self.__stepNum = 0


    def __str__(self):

        strList = [str(j).center(6) if j else ' ' * 6 for i in self.__gameMap for j in i]

        return (
            ' ------ ------ ------ ------ \n'
            '|      |      |      |      |\n'
            '|%s|%s|%s|%s|\n'
            '|      |      |      |      |\n'
            ' ------ ------ ------ ------ \n'
            '|      |      |      |      |\n'
            '|%s|%s|%s|%s|\n'
            '|      |      |      |      |\n'
            ' ------ ------ ------ ------ \n'
            '|      |      |      |      |\n'
            '|%s|%s|%s|%s|\n'
            '|      |      |      |      |\n'
            ' ------ ------ ------ ------ \n'
            '|      |      |      |      |\n'
            '|%s|%s|%s|%s|\n'
            '|      |      |      |      |\n'
            ' ------ ------ ------ ------ \n'
            '\nStep: %d' % (
            strList[0], strList[1], strList[2], strList[3],
            strList[4], strList[5], strList[6], strList[7],
            strList[8], strList[9], strList[10], strList[11],
            strList[12], strList[13], strList[14], strList[15],
            self.__stepNum,
        ))


    def createNewNum(self):

        idxList = [(i, j) for i in range(4) for j in range(4) if self.__gameMap[i, j] == 0]
        x, y = random.choice(idxList)
        self.__gameMap[x, y] = random.choice((1, 2))


    def pressLeft(self):

        moveBool = False

        for numLine in self.__gameMap:

            tarIdx = 0

            for idx in [1, 2, 3]:

                if numLine[idx]:

                    if numLine[tarIdx] == 0:

                        numLine[tarIdx] = numLine[idx]
                        numLine[idx] = 0
                        moveBool = True

                    elif numLine[tarIdx] == numLine[idx]:

                        numLine[tarIdx] *= 2
                        numLine[idx] = 0
                        tarIdx += 1
                        moveBool = True

                    else:

                        tarIdx += 1

                        if idx > tarIdx:
                            numLine[tarIdx] = numLine[idx]
                            numLine[idx] = 0
                            moveBool = True

        self.afterPress(moveBool)


    def pressRight(self):

        moveBool = False

        for numLine in self.__gameMap:

            tarIdx = 3

            for idx in [2, 1, 0]:

                if numLine[idx]:

                    if numLine[tarIdx] == 0:

                        numLine[tarIdx] = numLine[idx]
                        numLine[idx] = 0
                        moveBool = True

                    elif numLine[tarIdx] == numLine[idx]:

                        numLine[tarIdx] *= 2
                        numLine[idx] = 0
                        tarIdx -= 1
                        moveBool = True

                    else:

                        tarIdx -= 1

                        if idx < tarIdx:
                            numLine[tarIdx] = numLine[idx]
                            numLine[idx] = 0
                            moveBool = True

        self.afterPress(moveBool)


    def pressUp(self):

        moveBool = False

        for colIdx in range(4):

            numLine = self.__gameMap[:,colIdx]
            tarIdx = 0

            for idx in [1, 2, 3]:

                if numLine[idx]:

                    if numLine[tarIdx] == 0:

                        numLine[tarIdx] = numLine[idx]
                        numLine[idx] = 0
                        moveBool = True

                    elif numLine[tarIdx] == numLine[idx]:

                        numLine[tarIdx] *= 2
                        numLine[idx] = 0
                        tarIdx += 1
                        moveBool = True

                    else:

                        tarIdx += 1

                        if idx > tarIdx:
                            numLine[tarIdx] = numLine[idx]
                            numLine[idx] = 0
                            moveBool = True

        self.afterPress(moveBool)


    def pressDown(self):

        moveBool = False

        for colIdx in range(4):

            numLine = self.__gameMap[:,colIdx]
            tarIdx = 3

            for idx in [2, 1, 0]:

                if numLine[idx]:

                    if numLine[tarIdx] == 0:

                        numLine[tarIdx] = numLine[idx]
                        numLine[idx] = 0
                        moveBool = True

                    elif numLine[tarIdx] == numLine[idx]:

                        numLine[tarIdx] *= 2
                        numLine[idx] = 0
                        tarIdx -= 1
                        moveBool = True

                    else:

                        tarIdx -= 1

                        if idx < tarIdx:
                            numLine[tarIdx] = numLine[idx]
                            numLine[idx] = 0
                            moveBool = True

        self.afterPress(moveBool)


    def winCheck(self):

        for i in self.__gameMap:
            if 2048 in i:
                return True

        return False


    def loseCheck(self):

        for line in self.__gameMap:

            if 0 in line:
                return False

            for idx in range(3):
                if line[idx] == line[idx + 1]:
                    return False

        for colIdx in range(4):

            colList = self.__gameMap[:, colIdx]

            for idx in range(3):
                if colList[idx] == colList[idx + 1]:
                    return False

        return True


    def afterPress(self, moveBool):

        if moveBool:
            self.__stepNum += 1
            self.createNewNum()

        if self.winCheck():
            os.system('cls')
            print(self)
            print('\nYou Win!')
            os.system('pause')
            sys.exit(0)

        if self.loseCheck():
            os.system('cls')
            print(self)
            print('\nYou Lose!')
            os.system('pause')
            sys.exit(0)


    def Run(self):

        os.system('cls')
        print(self)

        while True:

            msvcrt.getch()
            inputChar = msvcrt.getch()

            if inputChar == b'H':
                self.pressUp()
            elif inputChar == b'P':
                self.pressDown()
            elif inputChar == b'K':
                self.pressLeft()
            elif inputChar == b'M':
                self.pressRight()

            os.system('cls')
            print(self)


################################################################################
# Main Program Define
################################################################################

def main():

    gameObj = Game()
    gameObj.Run()


if __name__ == '__main__':
    main()