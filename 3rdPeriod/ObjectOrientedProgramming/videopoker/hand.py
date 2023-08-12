from baralho import Baralho
from baralho import cartaToString

#a classe hand armazena instâncias da classe 
# baralho que representam cada carta
class Hand:
    #a função __init__ pega 5 cartas do baralho
    def __init__(self):
        self.hand = []
        self.baralho = Baralho()
        self.baralho.embaralhar()
        for i in range(5):
            self.hand.append(self.baralho.pegarCarta())
        
    #retorna as 5 cartas que estão na mão
    def olharCartas(self):
        return self.hand

    #substitui as cartas passadas como argumento por novas
    def trocarCartas(self, string):
        vetBool = self.strToBool(string)
        for i in range(5):
            if(vetBool[i] == True):
                self.hand[i] = self.baralho.pegarCarta()
      
    #transforma a string em um vetor booleano
    def strToBool(self, string):
        array = []
        for i in range(5):
            array.append(False)

        for i in range(len(string)):
            if(string[i] != ' '):
                c = int(string[i])
            array[c-1] = True
        return array

    #representação gráfica da mão
    def __str__(self):
        retorno = ""
        print("1 2 3 4 5")
        for i in range(5):
            retorno += cartaToString(self.hand[i]) + " "
        return retorno
