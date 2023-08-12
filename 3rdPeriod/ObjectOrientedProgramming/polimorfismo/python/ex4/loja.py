from produto import *

class Loja():
    def __init__(self):
        self.loja = []

    def buscaIndice(self, codigo:int):
        for i in range(len(self.loja)):
            if(codigo == self.loja[i].codigo):
                return i
        return -1  

    def adicionar(self, p:Produto):
        indice = self.buscaIndice(p.codigo)
        if(indice != -1 and isinstance(p, self.loja[indice])):
            self.loja[indice].quantidade += p.quantidade
        else:
            self.loja.append(p)

    def mostrarEstoque(self):
        if(len(self.loja) != 0):
            for produto in self.loja:
                print(produto)
        else:
            print("Loja vazia! ")

    def imprimirProduto(self, codigo):
        indice = self.buscaIndice(codigo)
        if(indice != -1):
            print(self.loja[indice])
        else:
            print("Produto não encontrado na loja.")

    def removerProduto(self, codigo, quantidade):
        indice = self.buscaIndice(codigo)
        if(indice != -1):
            dif = self.loja[indice].quantidade - quantidade
            if(dif < 0):
                print("Erro! Só existem {} desse produto. ".format(self.loja[indice].quantidade))
            elif(dif == 0):
                self.loja.pop(indice)
            else:
                self.loja[indice].quantidade = dif

        else:
            print("Produto não encontrado")

    def imprimirTudo(self):
        for produto in self.loja:
            print(produto)

    def novoProduto(self, codigo, entrada):
        nome = input("Nome: ")
        quantidade = int(input("Quantidade: "))
        if(entrada == 1):
            self.adicionar(DVD(nome, codigo, quantidade))
        if(entrada == 2):
            artista = input("Artista: ")
            self.adicionar(CD(nome, codigo, quantidade, artista))
        if(entrada == 3):
            autor = input("Autor: ")
            self.adicionar(Livro(nome, codigo, quantidade, autor))
        

