/*1 trouver le dernier élément d'une liste
my_last(D, [D]).
my_last(X, [T|Q]) :- my_last(X, Q).

/*2 Trouver l'avant dernier élément d'une liste
my_forlast(D, [D, _]).
my_forlast(X, [T|Q]) :- my_forlast(X, Q).

/*exercice supplémentaire : représenter l'exo 7 du tp 1 en liste :
/*
voyage(X, Y, [[X, Y, Z]]) : - voyageT(X, Y, Z).
voyage(X, Y, [[X, Z, T] |R]) :- voyageT(X, Z, T), voyage(Z, Y, R).

/* 3 trouver le Kième élément
element_at(X, [X|L], 1).
element_at(X, [T|Q], N) :- K is N-1, element_at(X, Q, K).
*//*
4 Trouver le nbre d element d une liste
nbre_elem([X], 1).
nbre_elem([_|Q], X) :- nbElem(Q, K), X is K+1.

5 inverser une liste
inverse([], X, X).
inverse(L1, L2) :- inverse(L1, [], L2).
inverse([T|Q], Acc, L):- inverse(Q, [T|Acc], L).

6 Indiquer si une liste est un palindrome
palindrome(X) :- inverse(X, L), X = L.
*/
/*7 Aplatir une liste composée de liste
my_flatten([],[]).
my_flatten([[T|Q]|Z], R):-  append (T,Q, C), my_flatten(L, R).

my_flatten([T|Q], X) :- is_list(T), my_flatten(T,X).
%my_flatten([T|Q], X) :- 

8 Eliminer les éléments consécutifs et identiques d'une liste d'éléments


%TD2
increment(X, Y):- X is Y -1.

sum(X, Y, Z):- Z is X+Y.

addone([],[]).
addone([T|Q], [B|L]):- B is A+1, addone(L|Q). .
*/

p(1).
p(2):- !.
p(3).
