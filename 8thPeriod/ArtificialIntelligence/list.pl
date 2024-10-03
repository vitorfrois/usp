element(X,[X|_]).

element(X,[_|T]) :-
	element(X,T).

append([], L2, L2).

append([H1|T1], L2, [H1|T]) :-
	append(T1, L2, T).
