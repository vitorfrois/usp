import random

class Baralho: 
    ultima = {} 
    
    def embaralhar(self):
        random.shuffle(self.carta)
    
    def __init__(self):
        self.carta = []
        for i in range(4):
            for j in range(13):
                self.carta.append({
                    "naipe": i,
                    "valor": j
                })    
        self.embaralhar()

    def pegarCarta(self):
        self.ultima = self.carta.pop()
        return self.ultima

    def pegarUltima(self):
        return self.ultima

    def main():
        baralho = Baralho()
        baralho.embaralhar()
        print(baralho.pegarCarta())
        print(baralho.pegarCarta())

def cartaToString(carta):
    if(carta["valor"] == 0):
        if(carta["naipe"] == 0): return "🂢"
        if(carta["naipe"] == 1): return "🂲"
        if(carta["naipe"] == 2): return "🃂"
        if(carta["naipe"] == 3): return "🃒"
    if(carta["valor"] == 1):
        if(carta["naipe"] == 0): return "🂣"
        if(carta["naipe"] == 1): return "🂳"
        if(carta["naipe"] == 2): return "🃃"
        if(carta["naipe"] == 3): return "🃓"
    if(carta["valor"] == 2):
        if(carta["naipe"] == 0): return "🂤"
        if(carta["naipe"] == 1): return "🂴"
        if(carta["naipe"] == 2): return "🃄"
        if(carta["naipe"] == 3): return "🃔"
    if(carta["valor"] == 3):
        if(carta["naipe"] == 0): return "🂥"
        if(carta["naipe"] == 1): return "🂵"
        if(carta["naipe"] == 2): return "🃅"
        if(carta["naipe"] == 3): return "🃕"
    if(carta["valor"] == 4):
        if(carta["naipe"] == 0): return "🂦"
        if(carta["naipe"] == 1): return "🂶"
        if(carta["naipe"] == 2): return "🃆"
        if(carta["naipe"] == 3): return "🃖"
    if(carta["valor"] == 5):
        if(carta["naipe"] == 0): return "🂧"
        if(carta["naipe"] == 1): return "🂷"
        if(carta["naipe"] == 2): return "🃇"
        if(carta["naipe"] == 3): return "🃗"
    if(carta["valor"] == 6):
        if(carta["naipe"] == 0): return "🂨"
        if(carta["naipe"] == 1): return "🂸"
        if(carta["naipe"] == 2): return "🃈"
        if(carta["naipe"] == 3): return "🃘"
    if(carta["valor"] == 7):
        if(carta["naipe"] == 0): return "🂩"
        if(carta["naipe"] == 1): return "🂹"
        if(carta["naipe"] == 2): return "🃉"
        if(carta["naipe"] == 3): return "🃙"
    if(carta["valor"] == 8):
        if(carta["naipe"] == 0): return "🂪"
        if(carta["naipe"] == 1): return "🂺"
        if(carta["naipe"] == 2): return "🃊"
        if(carta["naipe"] == 3): return "🃚"
    if(carta["valor"] == 9):
        if(carta["naipe"] == 0): return "🂫"
        if(carta["naipe"] == 1): return "🂻"
        if(carta["naipe"] == 2): return "🃋"
        if(carta["naipe"] == 3): return "🃛"
    if(carta["valor"] == 10):
        if(carta["naipe"] == 0): return "🂭"
        if(carta["naipe"] == 1): return "🂽"
        if(carta["naipe"] == 2): return "🃍"
        if(carta["naipe"] == 3): return "🃝"
    if(carta["valor"] == 11):
        if(carta["naipe"] == 0): return "🂮"
        if(carta["naipe"] == 1): return "🂾"
        if(carta["naipe"] == 2): return "🃎"
        if(carta["naipe"] == 3): return "🃞"
    if(carta["valor"] == 12):
        if(carta["naipe"] == 0): return "🂡"
        if(carta["naipe"] == 1): return "🂱"
        if(carta["naipe"] == 2): return "🃁"
        if(carta["naipe"] == 3): return "🃑"