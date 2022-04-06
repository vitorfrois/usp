from MyMath import sqrt

class main():
    try:
        x = float(input("Insira um número: "))
    except ValueError:
        print("Número inválido! ")
        exit()
    print("Raiz quadrada de {:f} é {:f}".format(x, sqrt(x)))

