byCar(auckland, hamilton).
byCar(hamilton, raglan).
byCar(valmont, saarbruecken).
byCar(valmont, metz).

byTrain(metz, franckfurt).
byTrain(saarbruecken, franckfurt).
byTrain(metz, paris).
byTrain(saarbruecken, paris).

byPlane(franckfurt,bangkok).
byPlane(franckfurt,singapore).
byPlane(paris,losAngeles).
byPlane(bangkok,auckland).
byPlane(singapore,auckland).
byPlane(losAngeles, auckland).

voyage(X, Y) :- byCar(X, Y); byTrain(X, Y); byPlane(X, Y).
voyage(X, Y) :- voyage(X, Z),(byTrain(Z, Y); byCar(Z, Y);byPlane(Z, Y)).

voyage(X, Y, byCar(X, Y)) :- byCar(X, Y).
voyage(X, Y, byTrain(X, Y)) :- byTrain(X, Y).
voyage(X, Y, byPlane(X, Y)) :- byPlane(X, Y).

voyage(X, Y, byCar(X, Z, V)) :- byCar(X, Z) , voyage(Z, Y, V).
voyage(X, Y, byTrain(X, Z, V)) :- byTrain(X, Z), voyage(Z, Y, V).
voyage(X, Y, byPlane(X, Z, V)) :- byPlane(X, Z), voyage(Z, Y, V).
