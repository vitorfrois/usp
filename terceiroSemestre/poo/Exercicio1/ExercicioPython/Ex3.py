class main():
    try:
        n = int(input("Insira um inteiro: "))
    except ValueError:
        print("Número inválido! ")
        exit()
    for i in range(n, 0, -1):
        for j in range(i): 
            print("*", end = "")
        print("\n")