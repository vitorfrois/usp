import unittest as ut
from Placar import Placar

class TestePlacar(ut.TestCase):
    
    def testGetScore(self):
        placar = Placar()	

        placar.add(1, [1,1,1,1,1])
        self.assertEqual(placar.getScore(0), 5)
        self.assertEqual(placar.getScore(), 5)

        placar.add(2, [2,2,2,2,2])
        self.assertEqual(placar.getScore(), 15)

        placar.add(3, [3,3,3,3,3])
        self.assertEqual(placar.getScore(), 30)

        placar.add(4, [4,4,4,4,4])
        self.assertEqual(placar.getScore(), 50)

        placar.add(5, [5,5,5,5,5])
        self.assertEqual(placar.getScore(), 75)

        placar.add(6, [6,6,6,6,6])
        self.assertEqual(placar.getScore(), 105)

        placar.add(7, [6,6,6,5,5])
        self.assertEqual(placar.getScore(), 120)

        placar.add(8, [1,2,3,4,5])
        self.assertEqual(placar.getScore(), 140)

        placar.add(9, [6,6,6,6,5])
        self.assertEqual(placar.getScore(), 170)

        placar.add(10, [6,6,6,6,6])
        self.assertEqual(placar.getScore(), 210)

    def testToString(self):
        placar = Placar()
        placar.add(1, [1,1,1,1,1])
        s =  " 5     |   (7)    |  (4) \n"
        s += "-------|----------|-------\n"
        s += "(2)    |   (8)    |  (5) \n"
        s += "-------|----------|-------\n"
        s += "(3)    |   (9)    |  (6) \n"
        s += "-------|----------|-------\n"
        s += "       |   (10)   |\n"
        s += "       +----------+\n"
        self.assertEqual(s, placar.__str__());

    def testPosicaoOcupada(self):
        placar = Placar()
        self.assertRaises(IndexError, placar.add, 0, [1,1,1,1,1])

    def testPosicaoInvalida(self):
        placar = Placar()
        placar.add(1, [1,1,1,1,1])
        self.assertRaises(ValueError, placar.add, 1, [1,1,1,1,5])

    def testGetTaken(self):
        placar = Placar()
        self.assertEqual(False, placar.getTaken(1))
    
    def testGetName(self):
        placar = Placar()
        self.assertEqual("Ones", placar.getName(0))