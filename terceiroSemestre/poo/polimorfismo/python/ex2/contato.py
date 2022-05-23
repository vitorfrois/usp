class Contato:
    def __init__(self, nome, endereço, email):
        self.nome = nome
        self.endereço = endereço
        self.email = email
        
    def __str__(self):
        print("Nome :" + self.nome)
        print("Endereço: " + self.endereço)
        print("email: " + self.email)

        
