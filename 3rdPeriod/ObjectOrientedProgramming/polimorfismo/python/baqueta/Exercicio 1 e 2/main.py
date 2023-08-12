from agenda import PessoaFisica, PessoaJuridica, Agenda

def main():
    a = Agenda()
    p1 = PessoaFisica(123456, "09/06/2003", "solteiro", "Pedro", "Rua 123", "pedro@email.com")
    p2 = PessoaJuridica(345, 666, "ong", "João", "Rua LLL", "joao@email.com")
    p3 = PessoaFisica(654321, "07/07/2007", "casado", "Lucas", "Rua X", "lucas@email.com")
    p4 = PessoaFisica(777777, "01/12/1997", "viúvo", "Paulo", "Avenida São Carlos", "paulo@bahoo.com")

    # Adicionando pessoas
    a.add_pessoa(p1)
    a.add_pessoa(p2)
    a.add_pessoa(p3)
    a.add_pessoa(p4)
    print(a)

    # Ordenando a agenda
    a.ordenar()
    print(a)

    # Removendo uma pessoa
    a.rem_pessoa("Pedro")
    print(a)

    # Pesquisando uma pessoa
    p = a.pesquisa_nome("João")
    print(p)

    p = a.pesquisa_cpf_cnpj(654321)
    print(p)

if __name__ == "__main__":
    main()