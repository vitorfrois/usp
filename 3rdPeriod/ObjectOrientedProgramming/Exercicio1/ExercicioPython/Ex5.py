import MyMath as m

class main():
    try:
        n = int(input("Insira um número inteiro: "))
    except ValueError():
        print("Número inválido! ")
        exit()
    original = n
    while(m.isPrime(n) == False):
        n-=1
    print("O maior número primo abaixo de {} é {}".format(original, n))    