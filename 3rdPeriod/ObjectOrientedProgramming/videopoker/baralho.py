import random

class Baralho: 
    ultima = {} 
    
    #embaralha a lista de cartas
    def embaralhar(self):
        random.shuffle(self.carta)
    
    #cria e inicializa uma lista de cartas
    def __init__(self):
        self.carta = []
        for i in range(4):
            for j in range(13):
                self.carta.append({
                    "naipe": i,
                    "valor": j
                })    
        self.embaralhar()

    #pega uma nova carta da lista de cartas
    def pegarCarta(self):
        self.ultima = self.carta.pop()
        return self.ultima

#função que retorna a representação visual de cada carta
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