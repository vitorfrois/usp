from contato_fisico import * 
from contato_juridico import *
from contato import *
from agenda import *

SAIR = 0
ADICIONAR = 1
REMOVER = 2
PESQUISAR = 3
IMPRIMIR = 4

def main():
    print("Bem vindo a agenda online! ")
    agenda = Agenda()
    opcao = -1
    while(opcao != SAIR):
        print("0 - SAIR")
        print("1 - ADICIONAR")
        print("2 - REMOVER")
        print("3 - PESQUISAR")
        print("4 - IMPRIMIR")
        opcao = int(input("Escolha uma opção: "))
        
        if(opcao == ADICIONAR):
            entrada = int(input("Digite 1 para físico e 2 para jurídico: "))
            nome = input("Nome: ")
            endereço = input("Endereço: ") 
            email = input("email: ") 
            if(entrada == 1):
                nascimento = input("Data de nascimento: ") 
                estadoCivil = input("Estado civil: ")
                cpf = input("CPF: ")
                agenda.adicionar(ContatoFisico(nome, endereço, email, nascimento, estadoCivil, cpf))
            elif (entrada == 2):
                razao = input("Razão social: ")
                cnpj = input("CNPJ: ")
                agenda.adicionar(ContatoJuridico(nome, endereço, email, razao, cnpj))
        elif(opcao == REMOVER):
            cadastro = input("Digite o número de CPF/CNPJ a ser removido: ")
            agenda.removerCadastro(cadastro)
        elif(opcao == PESQUISAR):
            cadastro = input("Digite o número de CPF/CNPJ a ser pesquisado: ")
            agenda.imprimirCadastro(cadastro)
        elif(opcao == IMPRIMIR):
            agenda.imprimirTudo()

        if(opcao != 0):
            while(opcao != ""):
                opcao = input("Pressione ENTER para continuar")


main()