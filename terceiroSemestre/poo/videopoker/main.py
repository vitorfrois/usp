from baralho import Baralho
from hand import Hand
from aposta import Aposta

def main():
    aposta = -1
    # print("\u2660")
    aposta = Aposta()
    dinheiro = 200
    entrada = ""
    print("Bem vindo ao jogo de videopoker! ")
    # print("Você possui {} créditos.".format(dinheiro))
    valorAposta = 0
    while(entrada != 'sair'):
        cartas = Hand()
        print("Você possui {} créditos.".format(dinheiro))
        condicao = True
        while(condicao):
            try:
                valorAposta = int(input("Quanto você deseja apostar? "))
            except:
                print("Insira um inteiro! Nenhum crédito será apostado. ")
                valorAposta = 0
            if(valorAposta >= dinheiro or valorAposta <= 0):
                print("O valor deve ser maior que 0 e menor ou igual ao número de créditos. ")
            else:
                condicao = False

        print(cartas)
        for i in range(2):
            entrada = input("Insira o número das cartas que deseja trocar separadas por espaços: ")
            try:
                cartas.trocarCartas(entrada)
            except IndexError:
                print("Insira um número entre 1 e 5! ")
                i -= 1
            print(cartas)

        dinheiro -= valorAposta
        valorAposta = aposta.retorno(cartas.pegarCartas(), valorAposta)
        print("Sua aposta deu {} créditos de retorno. ".format(valorAposta))
        dinheiro += valorAposta
        entrada = input("Digite 'sair' para sair ou aperte ENTER para continuar. ")
        if(dinheiro <= 1):
            print("Seus créditos acabaram! ")
            entrada = "sair"

main()