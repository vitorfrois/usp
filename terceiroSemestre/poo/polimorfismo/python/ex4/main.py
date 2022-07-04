from loja import *

SAIR = 0
ADICIONAR = 1
REMOVER = 2
PESQUISAR = 3
IMPRIMIR = 4

def main():
    loja = Loja()
    opcao = -1
    while(opcao != SAIR):
        print("\033[H\033[J", end="")
        print("Bem vindo a lojinha online! ")
        print("0 - SAIR")
        print("1 - ADICIONAR")
        print("2 - REMOVER")
        print("3 - PESQUISAR")
        print("4 - IMPRIMIR")
        try:
            opcao = int(input("Escolha uma opção: "))
        except:
            print("Insira um inteiro")
        #adiciona novos produtos na loja
        #caso o produto já exista, há a possibilidade de substituir ou incrementar a quantidade
        if(opcao == ADICIONAR):
            #leitura da entrada
            entrada = -1
            while(entrada != 1 and entrada != 2 and entrada != 3):
                try:
                    entrada = int(input("1 para DVD, 2 para CD e 3 para Livro: "))
                except:
                    print("Insira 1, 2 ou 3")
                    entrada = -1

            #leitura do codigo de barras
            codigo = -1
            while(codigo == -1):
                try:
                    codigo = int(input("Código: "))
                except:
                    print("Insira um inteiro! ")
                    codigo = -1
            
            resposta = 'i'
            indice = loja.buscaIndice(codigo)
            if(indice != -1):
                #se já existirem produtos na loja com o código inserido
                while(resposta != 1 and resposta != 2 and resposta != 3):
                    print("Já existe um registro com esse código.")
                    resposta = int(input("Digite 1 para aumentar a quantidade do produto, 2 para criar novo produto ou 3 para cancelar: "))
                    if(resposta == 1):
                        quantidade = int(input("Quantidade: "))
                        loja.loja[indice].quantidade += quantidade
                    elif(resposta == 2):
                        loja.removerProduto(codigo, loja.loja[indice].quantidade)
                        loja.novoProduto(codigo, entrada)
                    elif(resposta == 3):
                        break          
            else:      
                loja.novoProduto(codigo, entrada)

        #remove pelo código  
        elif(opcao == REMOVER):
            codigo = int(input("Digite o código de barras do registro a ser removido: "))
            indice = loja.buscaIndice(codigo)
            if(indice != -1):
                print("Existem {} desse produto na loja. ".format(loja.loja[indice].quantidade))
                quantidade = int(input("Insira a quantidade de produtos que deseja remover: "))
                loja.removerProduto(codigo, quantidade)
            else:
                print("Produto não encontrado na loja.")

        #pesquisa produtos pelo código       
        elif(opcao == PESQUISAR):
            codigo = int(input("Digite o código de barras a ser pesquisado: "))
            loja.imprimirProduto(codigo)
        
        #imprime todos os produtos da loja
        elif(opcao == IMPRIMIR):
            loja.imprimirTudo()

        if(opcao != 0):
            while(opcao != ""):
                opcao = input("Pressione ENTER para continuar")



main()
