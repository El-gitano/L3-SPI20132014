% Jeu de la vie en Prolog

% Nous allons utiliser des listes pour faire les lignes de cellules

% On initialise le jeu en passant en parametre le nombre de ligne, qui est aussi celui de colonne, et la liste qu on attennd
initJeu(N, L):- initLigne(N,N, L).

% On met une liste vide si on arrive a la fin, sinon on ajoute une colonne et on passe au reste de la liste
initLigne(_, 0, []).
initLigne(N, K, [T|Q]):- initColonne(N, T), I is K-1, initLigne(N, I, Q).

% une colonne est constitué d une liste avec en tete soit un - soit une *, et du reste de la colonne. on soccupe de la tete et on passe au reste de la liste
initColonne(0, []).
initColonne(K, [T|Q]) :- X is random(2), formate(X, T), Z is K-1, initColonne(Z, Q).
% 
formate(0, '-').
formate(1, '*').

% Pour verifier l etat d une case dont on passe les coordonnees en param, on a besoin du predicat element at
element_at(0, [T|Q], T).
element_at(N, [T|Q], X) :- K is N-1, element_at(K, Q, X).

etatCase(J, X, Y, E):- element_at(X, J, L) , element_at(Y, L, E), !.
etatCase(_, _, _, '-').

valeurCase(X, Y, J, 1):- etatCase(J, X, Y, '*'), !.
valeurCase(_, _, _, 0).

nbVoisins(X, Y, J, V) :-
    Xmoins1 is X -1,
    Xplus1 is X + 1, 
    Ymoins1 is Y -1,
    Yplus1 is Y + 1,
    valeurCase(Xmoins1, Ymoins1, J, V1),
    valeurCase(X, Ymoins1, J, V2), 
    valeurCase(Xplus1, Ymoins1, J, V3),
    valeurCase(Xmoins1, Y, J, V4),
    valeurCase(Xplus1, Y, J, V5),
    valeurCase(Xmoins1, Yplus1, J, V6),
    valeurCase(X, Yplus1, J, V7),
    valeurCase(Xplus1, Yplus1, J, V8),
    V is V1 + V2 + V3 + V4 + V5 + V6 + V7 + V8.

prochaineGen(J, N, P):- initLigneNext(J,N, N, P).

initLigneNext(_, _, 0, []).
initLigneNext(J, N, K, [T|Q]):- 
    initColonneNext(J, K, N, T), I is K-1, initLigneNext(J, N, I, Q).

initColonneNext(_, _,0, []).
initColonneNext(J, K, C, [T|Q]):- 
    nbVoisins(K, C, J, X), etatCase(J, K, C, '*'), X > 1, X < 4, formate(1, T), I is C-1, initColonneNext(J, K, I, Q), !.
initColonneNext(J, K, C, [T|Q]):-
    nbVoisins(K, C, J, X), X = 3, formate(1, T), I is C-1, initColonneNext(J, K, I, Q), !.


initColonneNext(J, N, K, [T|Q]):- 
    formate(0, T), I is K-1, initColonneNext(J, N, I, Q).
