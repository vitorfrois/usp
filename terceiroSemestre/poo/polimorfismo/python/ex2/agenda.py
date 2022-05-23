from contato_fisico import * 
from contato_juridico import *
from contato import *

#define o método utilizado para ordenação
#como o cnpj possui mais caracteres, naturalmente
#ficara depois
def metodo(e):
    if(isinstance(e, ContatoFisico)):
        return e.cpf
    else:
        return e.cnpj

class Agenda():
    def __init__(self):
        self.agenda = []    

    def adicionar(self, p:Contato):
        self.agenda.append(p)

    def imprimirTudo(self):
        self.agenda.sort(key=metodo, reverse=True)
        if(len(self.agenda) != 0):
            for pessoa in self.agenda:
                pessoa.__str__()
        else:
            print("Agenda vazia! ")

    def imprimirCadastro(self, id):
        existente = False
        for pessoa in self.agenda:
            if(pessoa.cpf == id or pessoa.cnpj == id):
                pessoa.__str__()
                existente = True
        if(existente == False):
            print("Contato não encontrada na agenda")

    def removerCadastro(self, id):
        existente = False
        for i in range(len(self.agenda)):
            if(self.agenda[i].cpf == id or self.agenda[i].cnpj == id):
                self.agenda.pop(i)
                existente = True
        if(existente == False):
            print("Contato não encontrada na agenda")

    


        