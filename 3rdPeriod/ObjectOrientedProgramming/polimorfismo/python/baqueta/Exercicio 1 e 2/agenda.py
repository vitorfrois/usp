"""
Gerenciar uma agenda de Pessoas Física e Jurídicas
"""

from operator import attrgetter

class Pessoa():
    def __init__(self, nome:str, endereco:str, email:str):
        self.nome = nome
        self.endereco = endereco
        self.email = email

    def __str__(self):
        return f"{self.nome}, {self.endereco}, {self.email}"

class PessoaFisica(Pessoa):
    def __init__(self, cpf:int, nascimento:str, estado_civil:str, nome:str, endereco:str, email:str):
        super().__init__(nome, endereco, email)
        self.cpf = cpf
        self.nascimento = nascimento
        self.estado_civil = estado_civil

class PessoaJuridica(Pessoa):
    def __init__(self, cnpj:int, inscricao_estadual:int, razao_social:str, nome:str, endereco:str, email:str):
        super().__init__(nome, endereco, email)
        self.cnpj = cnpj
        self.inscricao_estadual = inscricao_estadual
        self.razao_social = razao_social

class Agenda():
    def __init__(self):
        self.pessoas = []

    def pesquisa_nome(self, nome:str) -> Pessoa:
        for pessoa in self.pessoas:
            if pessoa.nome == nome:
                return pessoa

        raise KeyError

    def pesquisa_cpf_cnpj(self, cpf_cnpj:int) -> Pessoa:
        for pessoa in self.pessoas:
            if isinstance(pessoa, PessoaFisica):
                if pessoa.cpf == cpf_cnpj:
                    return pessoa

            elif isinstance(pessoa, PessoaJuridica):
                if pessoa.cnpj == cpf_cnpj:
                    return pessoa

        raise KeyError

    def add_pessoa(self, p:Pessoa) -> None:
        self.pessoas.append(p)

    def rem_pessoa(self, nome=None, cpf_cnpj=None) -> None:
        if nome is not None:
            p = self.pesquisa_nome(nome)
            if p is not None:
                self.pessoas.remove(p)
                return

        if cpf_cnpj is not None:
            p = self.pesquisa_cpf_cnpj(cpf_cnpj)
            if p is not None:
                self.pessoas.remove(p)
                return

        raise KeyError("Pessoa não encontrada")

    def __sort(self, array:list, key):
        """
        Bubble Sort an array
        """
        for i in range(len(array)):
            for j in range(0, len(array) - 1 - i):
                if key(array[j]) > key(array[j + 1]):
                    temp = array[j]
                    array[j] = array[j+1]
                    array[j+1] = temp

    def ordenar(self) -> None:
        pfs = []
        pjs = []
        for pessoa in self.pessoas:
            if isinstance(pessoa, PessoaFisica):
                pfs.append(pessoa)
            else:
                pjs.append(pessoa)
        
        self.__sort(pfs, attrgetter('cpf'))
        self.__sort(pjs, attrgetter('cnpj'))

        self.pessoas = pfs + pjs

    def __str__(self) -> str:
        s = ''
        for pessoa in self.pessoas:
            if isinstance(pessoa, PessoaFisica):
                s += f"{pessoa.nome}\t{pessoa.cpf}\t[PF]\n"
            elif isinstance(pessoa, PessoaJuridica):
                s += f"{pessoa.nome}\t{pessoa.cnpj}\t[PJ]\n"

        return s