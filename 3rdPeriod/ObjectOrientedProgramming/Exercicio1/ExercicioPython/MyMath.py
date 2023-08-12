def abs(x):
    if(x < 0): 
        return x * -1;
    else: 
        return x;

def sqrt(x):
    x0 = x/10 
    x1 = x0+0.1;
    while(abs(x0-x1) > 0.00000001):
        x0 = x1;
        x1 = (x0 + (x/x0))/2.0;
    return x1

def isPrime(a):
    if a < 2: 
        return False
    for x in range(2, int(sqrt(a)) + 1):
        if a % x == 0:
            return False
    return True

def funcao(x):
    return (x*x*x) - (x*x) - (13*x) + (8)

def derivadaFuncao(x):
    return (3*x*x) - (2*x) - (13)

def bissecao():
    try:
        a = int(input("Insira o valor de a: "))
    except ValueError():
        print("Número inválido! ")
        exit()
    try:
        b = int(input("Insira o valor de b: "))
    except ValueError():
        print("Número inválido! ")
        exit()

    if(funcao(a) * funcao(b) >= 0):
        print("f(a) * f(b) >= 0. Insira novos valores de a e b")
        return

    c = 0.0
    iteracoes = 0
    while((b-a) >= 0.00000001):
        iteracoes += 1
        c = (a+b)/2
        if (funcao(c) == 0.0):
            exit()
        elif (funcao(c) * funcao(a) < 0): 
            b = c
        else: 
            a = c
        
    return c, iteracoes

def newtonRaphson(x0):

    x1 = funcao(x0);
    erro = abs((x1 - x0));
    iteracoes = 0;
    while(erro >= 0.00000001):
        iteracoes += 1
        x0 = x1
        x1 = x0 - (funcao(x0)/derivadaFuncao(x0))
        erro = abs((x1 - x0))
    
    return x1, iteracoes
