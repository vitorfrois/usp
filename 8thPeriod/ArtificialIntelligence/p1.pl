progenitor(sara,isaque).
progenitor(abraao,isaque).
progenitor(abraao,ismael).
progenitor(isaque,esau).
progenitor(isaque,jaco).
progenitor(jaco,jose).

gosta(joao,maria).
gosta(maria,lasanha).
gosta(maria,gato).

mulher(sara).

homem(abraao).
homem(isaque).
homem(ismael).
homem(esau).
homem(jaco).
homem(jose).

mae(X,Y):-
	progenitor(X,Y),
	mulher(X).

irmaos(X,Y):-
	progenitor(Z,X),
	progenitor(Z,Y).

avo(X,Y):-
	progenitor(Z,Y),
	progenitor(X,Z).

antecedente(X,Y):- progenitor(X,Y).
antecedente(X,Y):- 
	progenitor(X,Z),
	antecedente(Z,Y).

accMax([H|T], X, Max):-	
	H > X,
	accMax(T, H, Max).
accMax([H|T], X, Max):-	
	H =< X,
	accMax(T, H, Max).
accMax([], A, A).

max(L, X):-
	L = [H|_],
	accMax(L, H, X).


