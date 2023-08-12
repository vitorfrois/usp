import MyMath as m 

class main():
    try:
        x0 = int(input("Insira o chute inicial para calcular as "
                       "raízes de x³-x²-13x+8 através do método de "
                       "Newton Raphson. \nx0 = "))
    except ValueError:
        print("Número inválido! ")   
        exit()
    x1, iteracoes = m.newtonRaphson(x0)
    print("Foram necessarias {} iteracoes para encontrar a raiz {}".format(iteracoes, x1))