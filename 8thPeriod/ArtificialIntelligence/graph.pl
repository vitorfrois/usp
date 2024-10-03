aresta(a,b).
aresta(b,c).
aresta(c,d).
aresta(d,e).
aresta(e,c).
aresta(f,g).

conectado(A,B) :- aresta(A,B); aresta(B, A).
conectado(A,C,Path) :- 
	aresta(A,B),
	conectado(B,C,Path).

myDFS(D,D,Acc,[D|Acc]).

% Recursion
myDFS(O,D,Acc,Path) :-
    conectado(O,X),
    \+ member(X, Acc),
    myDFS(X,D,[O|Acc],Path).


