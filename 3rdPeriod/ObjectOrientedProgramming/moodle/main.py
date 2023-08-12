class Adivinha:
    def __init__(self, n):
        self.n = n

    def adivinhaNumero(self):
        adivinhou = False
        tentativas = 0
        menor = 0
        maior = self.n
        chute = Adivinha.media(menor, maior)
        while(adivinhou == False):
            tentativas += 1
            resposta = input("{} é o número? (m/M/a) ".format(chute))
            print(resposta)
            if(resposta == 'm'):
                maior = chute
                chute = Adivinha.media(menor, maior)
            elif(resposta == 'M'):
                menor = chute
                chute = Adivinha.media(menor, maior)
            elif(resposta == 'a'):
                adivinhou = True

        print("Foram necessárias {} tentativas.".format(tentativas))
        print("O número que você pensou foi {}!".format(chute))

    def media(a, b):
        return int((a + b)/2)


def main():
    N = int(input("Insira N: "))
    chute = Adivinha(N)
    chute.adivinhaNumero()

main()