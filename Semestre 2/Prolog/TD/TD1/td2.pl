split([], [], []).
split([X|Q], [X|P], N):- X>= 0, split(Q, P, N), !.
split([X|Q], P, [X|N]):- X< 0, split(Q, P, N).
