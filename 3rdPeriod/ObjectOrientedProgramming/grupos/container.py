class Container():
    def __init__(self, mensagem, tabela=None):
        self.mensagem = mensagem
        self.lista = []
        if(tabela != None):
            self.lista = tabela
        
    def adicionar(self, item):
        self.lista.append(item)

    def remover(self, item):
        self.lista.remove(item)

    def __str__(self):
        if(len(self.lista) == 0):
            return self.mensagem + "(vazio)\n"
        string = ""
        string += self.mensagem + "\n"
        for itens in self.lista:
            string += itens + "\n"
        return string 