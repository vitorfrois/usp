import numpy as np

copas = np.zeros(12)
espadas = np.zeros(12)
ouros = np.zeros(12)
paus = np.zeros(12)



cardsString = input()

lenght = int(len(cardsString)/3)

printCopas = 'a'
printEspadas = 'a'
printOuros = 'a'
printPaus = 'a'
for x in range (lenght):
    num = int(cardsString[3*x] + cardsString[3*x+1])
    if (cardsString[3*x+2] == 'C'):
        copas[num] += 1
        if(copas[num] > 1):
            printCopas = 'erro'

    elif (cardsString[3*x+2] == 'E'):
        espadas[num] += 1
        if(espadas[num] > 1):
            printEspadas = 'erro'

    elif (cardsString[3*x+2] == 'U'):
        ouros[num] += 1
        if(ouros[num] > 1):
            printOuros = 'erro'

    elif (cardsString[3*x+2] == 'P'):
        paus[num] += 1
        if(paus[num] > 1):
            printPaus = 'erro'

copasSZ = 0
espadasSZ = 0
ourosSZ = 0
pausSZ = 0

for x in range (12):
    if copas[num] == 0:
        copasSZ += 1
    if espadas[num] == 0:
        espadasSZ += 1
    if ouros[num] == 0:
        ourosSZ += 1
    if paus[num] == 0:
        pausSZ += 1


if printCopas != 'erro':
    print(copasSZ)
else:
    print('erro')

if printEspadas != 'erro':
    print(espadasSZ)
else:
    print('erro')

if printOuros != 'erro':
    print(ourosSZ)
else:
    print('erro')

if printPaus != 'erro':
    print(pausSZ)
else:
    print('erro')
