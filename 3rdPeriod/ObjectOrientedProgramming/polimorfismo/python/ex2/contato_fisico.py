import contato

class ContatoFisico(contato.Contato):
    def __init__(self, nome, endereço, email, nascimento, estadoCivil, cpf):
        super().__init__(nome, endereço, email)
        self.nascimento = nascimento
        self.estadoCivil = estadoCivil
        self.cpf = cpf

    def __str__(self):
        super().__str__()
        print("Data de Nascimento = " + self.nascimento)
        print("Estado Civil: " + self.estadoCivil)
        print("CPF: " + self.cpf)

        