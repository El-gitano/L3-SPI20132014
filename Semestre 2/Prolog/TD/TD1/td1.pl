#1 trouver le dernier élément d'une liste
my_last(D, [D]).
my_last(X, [T|Q]) :- my_last(X, Q).

#2 Trouver l'avant dernier élément d'une liste
my_forlast(D, [D, _]).
my_forlast(X, [T|Q]) :- my_forlast(X, Q).

#exercice supplémentaire : représenter l'exo 7 du tp 1 en liste :

voyage(X, Y, [[X, Y, Z]]) : - voyageT(X, Y, Z).
voyage(X, Y, [[X, Z, T] |R]) :- voyageT(X, Z, T), voyage(Z, Y, R).

# 3 trouver le Kième élément
element_at(X, [X|L], 1).
element_at(X, [T|Q], N). :- K is N-1, element_at(X, Q, K).

#4 Trouver le nbre d element d une liste
nbre_elem([X], 1).
nbre_elem([_|Q], X) :- nbElem(Q, K), X is K+1.

#5 inverser une liste
inverse(L1, L2) :-inverse(L1, [], L2).
inverse([], X, X).
inverse([X|Q], Acc, L) :- inverse (Q, [T|Acc], L).

#6 Indiquer si une liste est un palindrome
