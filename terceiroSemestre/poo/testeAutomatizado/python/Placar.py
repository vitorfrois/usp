class Placar():

	def __init__(self):
		self.POSICOES = 10
		self.placar =  self.POSICOES * [0]
		self.taken = self.POSICOES * [False]
		self.nomes = ["Ones", "Twos", "Threes", "Fours", "Fives", 
		"Sixes", "Full", "Sequence", "Four of a kind", "General"]
	
	def __str__(self):
		s = ''
		for i in range(3):
			s += self.uma_linha(i) + "   |   "
			s += self.uma_linha(i+6) + "   |  "
			s += self.uma_linha(i+3) + "\n-------|----------|-------\n"
		s += "       |   " + self.uma_linha(9) + "   |"
		s += "\n       +----------+\n"
		return s

	def uma_linha(self,i):
		if i == 9:
			num = '{:^4d}'.format(self.placar[i]) if self.taken[i] else "({:2d})".format(i+1)
		else:
			num = '{:^4d}'.format(self.placar[i]) if self.taken[i] else "({:1d}) ".format(i+1)
		return num


	def add(self, posicao, dados):
		if posicao < 1 or posicao > self.POSICOES:
			raise IndexError("Valor da posição no placar é ilegal")
		if self.taken[posicao-1]:
			raise ValueError("Posição ocupada no placar")
		k = 0
		if posicao in range(1,7):
			k = Placar.conta(posicao,dados) * posicao
		elif posicao == 7:
			k = 15 if Placar.checkFull(dados) else 0
		elif posicao == 8:
			k = 20 if Placar.checkSeqMaior(dados) else 0
		elif posicao == 9:
			k = 30 if Placar.checkQuadra(dados) else 0
		else:
			k = 40 if Placar.checkQuina(dados) else 0
		self.placar[posicao-1] = k
		self.taken[posicao-1] = True
		
	def getScore(self, k = None):
		if k != None:
			return self.placar[k]
		t = 0
		for i in range(self.POSICOES):
			if self.taken[i]:
				t += self.placar[i]
		return t
		
	
	def getTaken(self, k):
		return self.taken[k]
		
	def getName(self, k):
		return self.nomes[k]
		
	@staticmethod	
	def conta(n, vet):
		cont = 0
		for i in vet:
			if i == n:
				cont += 1
		return cont
		
	@staticmethod	
	def checkFull(dados):
		v = sorted(dados)
		return (v[0] == v[1] and v[1] == v[2] and v[3] == v[4]) or \
		(v[0] == v[1] and v[2] == v[3] and v[3] == v[4])
             
	@staticmethod	
	def checkSeqMaior(dados):
		v = sorted(dados)
		return v[0]+1 == v[1] and v[1]+1 == v[2] and v[2]+1 == v[3]\
		and v[3]+1 == v[4]
		
	@staticmethod	
	def checkQuadra(dados):
		v = sorted(dados)
		return ( v[0] == v[1] and v[1] == v[2] and v[2] == v[3]) or\
		( v[1] == v[2] and v[2] == v[3] and v[3] == v[4])

	@staticmethod	
	def checkQuina(v):
		return  v[0] == v[1] and v[1] == v[2] and v[2] == v[2] and v[3] == v[4]