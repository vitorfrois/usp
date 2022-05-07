from baralho import Baralho
from baralho import cartaToString

class Hand:
    def __init__(self):
        self.hand = []
        self.baralho = Baralho()
        self.baralho.embaralhar()
        for i in range(5):
            self.hand.append(self.baralho.pegarCarta())
        
    def pegarCartas(self):
        return self.hand

    def trocarCartas(self, string):
        vetBool = self.strToBool(string)
        for i in range(5):
            if(vetBool[i] == True):
                self.hand[i] = self.baralho.pegarCarta()
      
    def strToBool(self, string):
        array = []
        for i in range(5):
            array.append(False)

        for i in range(len(string)):
            if(string[i] != ' '):
                c = int(string[i])
            array[c-1] = True
        return array


    def __str__(self):
        retorno = ""
        print("1 2 3 4 5")
        for i in range(5):
            retorno += cartaToString(self.hand[i]) + " "
        return retorno
