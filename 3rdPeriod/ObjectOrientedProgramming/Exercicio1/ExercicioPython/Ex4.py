class main():
    try:
        n = int(input("Insira um inteiro: "))
    except ValueError():
        print("Número inválido! ")
        exit()
    for i in range(n, 0, -1):
        for j in range(n-i): 
            print(" ", end = "")
        for j in range(i, 0, -1): 
            print("*", end = "")
        print("\n")