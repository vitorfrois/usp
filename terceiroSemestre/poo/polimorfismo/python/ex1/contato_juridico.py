import contato

class ContatoJuridico(contato.Contato):
    def __init__(self, nome, endereço, email, razaoSocial, cnpj):
        super().__init__(nome, endereço, email)
        self.razaoSocial = razaoSocial
        self.cnpj = cnpj

    def __str__(self):
        super().__str__()
        print("Razão Social: " + self.razaoSocial)
        print("CNPJ = " + self.cnpj)

    