class Aposta:
    def __init__(self):
        pass
        
    def DoisPares(self, contagem):
        count = 0
        for i in range(13):
            if(contagem[i] == 2):
                count += 1
        if(count == 2):
            return True
        return False

    def Trinca(self, contagem):
        count = 0
        for i in range(13):
            if(self.contagem[i] == 3):
                count += 1
        if(count == 1):
            return True
        return False

    def Straight(self, contagem):
        count = 0
        for i in range(13):
            if(self.contagem[i] == 1 and i < (13-4)):
                for j in range(i, i+5, 1):
                    if(self.contagem[j] == 1):
                        count += 1
                if(count == 5):
                    return True
                count = 0
        return False

    def Flush(self, cartas):
        count = 0
        if( cartas[0]["naipe"] == 
            cartas[1]["naipe"] == 
            cartas[2]["naipe"] == 
            cartas[3]["naipe"] == 
            cartas[4]["naipe"]):
            return True
        return False

    def FullHand(self, contagem):
        if(self.Trinca(contagem) and self.DoisPares(contagem)):
            return True
        return False

    def Quadra(self, contagem):
        count = 0
        for i in range(13):
            if(self.contagem[i] == 4):
                count += 1
        if(count == 1):
            return True
        return False

    def StraightFlush(self, contagem, cartas):
        if(self.Straight(contagem) and self.Flush(cartas)):
            return True
        return False

    def RoyalStraight(self, contagem):
        if( contagem[12] == 1 and
            contagem[11] == 1 and
            contagem[10] == 1 and
            contagem[9] == 1 and
            contagem[8] == 1):
            return True
        return False

    def RoyalStraightFlush(self, contagem, cartas):
        if(self.RoyalStraight(contagem) and self.Flush(cartas)):
            return True
        return False

            
    def retorno(self, cartas, dinheiro):
        self.contagem = []
        for i in range(13):
            self.contagem.append(0)
        for i in range(5):
            self.contagem[cartas[i]["valor"]] += 1

        if(self.RoyalStraightFlush(self.contagem, cartas) == True):
            return dinheiro * 200
        elif(self.StraightFlush(self.contagem, cartas) == True):
            return dinheiro * 100
        elif(self.Quadra(self.contagem) == True):
            return dinheiro * 50
        elif(self.FullHand(self.contagem) == True):
            return dinheiro * 20
        elif(self.Flush(cartas) == True):
            return dinheiro * 10
        elif(self.Straight(self.contagem) == True):
            return dinheiro * 5
        elif(self.Trinca(self.contagem) == True):
            return dinheiro * 2
        elif(self.DoisPares(self.contagem) == True):
            return dinheiro
        else:
            return 0

        #com o vetor de contagem é possível analisar
        #as apostas
        