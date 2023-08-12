class main():
    n = 1.0;
    menor = float('inf')
    maior = float('-inf')
    while(n != 0.0):
        try:
            n = float(input("Insira um número de ponto flutuante: "))    
        except ValueError():
            print("Número inválido! ")
            exit()
        if(n != 0):
            if(n < menor): 
                menor = n
            if(n > maior): 
                maior = n
        
    print("O maior é {} e o menor é {}".format(maior, menor));