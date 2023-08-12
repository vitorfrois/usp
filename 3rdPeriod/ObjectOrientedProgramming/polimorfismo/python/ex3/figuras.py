import math

class Figura():
    def __init__(self, cor, preenchido):
        self.cor = cor
        self.preenchido = preenchido

    def __str__(self):
        print("Cor: " + self.cor)
        print("Preenchido: " + self.preenchido + "\n")

class Retangulo(Figura):
    def __init__(self, altura, largura, cor, preenchido):
        self.altura = altura
        self.largura = largura
        self.area = altura * largura
        self.perimetro = 2 * altura + 2 * largura
        super().__init__(cor, preenchido)

    def __str__(self):
        print("O Retângulo possui")
        print("Largura: " + str(self.largura))
        print("Perímetro: " + str(self.perimetro))
        print("Área: " + str(self.area))
        super().__str__()

class Quadrado(Figura):
    def __init__(self, largura, cor, preenchido):
        self.largura = largura
        self.area = largura * largura
        self.perimetro = 4 * largura
        super().__init__(cor, preenchido)

    def __str__(self):
        print("O quadrado possui")
        print("Largura: " + str(self.largura))
        print("Perímetro: " + str(self.perimetro))
        print("Área: " + str(self.area))
        super().__str__()

def areaCirculo(raio):
    return math.pi * pow(raio, 2)

def perimetroCirculo(raio):
    return 2 * math.pi * raio

class Circulo(Figura):

    def __init__(self, raio, cor, preenchido):
        self.raio = raio
        self.area = areaCirculo(self.raio)
        self.perimetro = perimetroCirculo(self.raio)
        super().__init__(cor, preenchido)

    def __str__(self):
        print("O circulo possui")
        print("Raio: " + str(self.raio))
        print("Perímetro: " + str(self.perimetro))
        print("Área: " + str(self.area))
        super().__str__()

def main():
    circle = Circulo(10, "azul", "sim")
    square = Quadrado(10, "rosa", "não")
    rectangle = Retangulo(5, 9, "verde-limão", "não")
    circle.__str__()
    square.__str__()
    rectangle.__str__()



main()