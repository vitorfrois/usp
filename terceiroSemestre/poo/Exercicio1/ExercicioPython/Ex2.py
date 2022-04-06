from MyMath import sqrt

def baskhara(a, b, delta):
    r1 = (-b+sqrt(delta))/(2*a)
    r2 = (-b-sqrt(delta))/(2*a)
    return r1, r2

class main():

    try:
        a = int(input("Insira a: "))
    except ValueError:
        print("Número inválido!")
        exit()
    try:
        b = int(input("Insira b: "))
    except ValueError:
        print("Número inválido!")
        exit()
    try:
        c = int(input("Insira c: "))
    except ValueError:
        print("Número inválido!")
        exit()
    delta = b*b - (4 * a * c)
    if(delta < 0):
        print("Delta negativo. A função não possui raízes. Insira novos valores. ")
        exit()
    (r1, r2) = baskhara(a, b, delta)
    print("As raízes da equação são {:f} e {:f}.".format(r1, r2))

