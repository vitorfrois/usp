class Produto():
    def __init__(self, nome, codigo, quantidade):
        self.nome = nome
        self.codigo = codigo
        self.quantidade = quantidade

    def __str__(self):
        string = "Nome: "
        string += str(self.nome)
        string += "\nCódigo: " 
        string += str(self.codigo)
        string += "\nQuantidade: " 
        string += str(self.quantidade)
        return string

class CD(Produto):
    def __init__(self, nome, codigo, quantidade, artista):
        super().__init__(nome, codigo, quantidade)
        self.artista = artista

    def __str__(self):
        string = "CD\n" + super().__str__()
        string += "\nArtista: "
        string += self.artista
        return string

class DVD(Produto):
    def __init__(self, nome, codigo, quantidade):
        super().__init__(nome, codigo, quantidade)

    def __str__(self):
        return "DVD\n" + super().__str__()

class Livro(Produto):
    def __init__(self, nome, codigo, quantidade, autor):
        super().__init__(nome, codigo, quantidade)
        self.autor = autor

    def __str__(self):
        string = "Livro\nreturn" + super().__str__()
        string += "Autor "
        string += self.autor
        return string

