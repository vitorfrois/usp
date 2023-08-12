import MyMath as m 
 
class main():
    raiz, iteracoes = m.bissecao()
    if(raiz != None):
        print("A raiz da equação é {}.".format(raiz)) 
        print("Foram necessárias {} iterações para obter o resultado".format(iteracoes))
