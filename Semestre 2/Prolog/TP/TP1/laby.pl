connecte(1,2).
connecte(3,4).
connecte(5,6).
connecte(7,8).
connecte(9,10).
connecte(12,13).
connecte(13,14).
connecte(15,16).
connecte(17,18).
connecte(19,20).
connecte(4,1).
connecte(6,3).
connecte(4,7).
connecte(6,11).
connecte(14,9).
connecte(11,15).
connecte(16,12).
connecte(14,17).
connecte(16,19).

chemin(X, Y) :- connecte(X, Y).
chemin(X, Y) :- connecte(X, Z), chemin(Z, Y).
