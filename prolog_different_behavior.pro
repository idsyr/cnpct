r(r1, 30).
r(r2, 40).
par(par1, r1, r2).

r(r3, 50).
r(r4, 60).
seq(s1, r3, r4).

r(r5, 70).
r(r6, 80).
seq(s2, r5, r6).

%S2 = sequnce(r1, r2).
%Scheme = [s1,s2].

par_r(RET, Conname) :-
  par(Conname, R1, R2), r(R1, R1V), r(R2, R2V), plus(R1V, R2V, RET).

seq_r(RET, Conname) :-
  seq(Conname, R1, R2), 
  r(R1, R1V), 
  r(R2, R2V), 
  RET = (R1V*R2V)/(R1V+R2V).

member(X, [X | Tail]).
member(X, [Head | Tail]) :-
  member(X, Tail).

ember(X, [X | Tail]).

del(TAR, [TAR | Tail], Tail).
del(TAR, [SKIP | Tail], [SKIP | Dest]) :-
  del(TAR, Tail, Dest).

find_r(RET, Scheme) :-
  member(X, Scheme),
  seq_r(RET, X).

concat([], E, E).
concat([RET | TL], TAR2, [RET | TR]):-
  concat(TT, TAR2, TR).

same(L, L).

nos(L1, L2).

sublist(S,L) :-
  concat(L10, L20, L),
  concat(S, L15, L20). 
  
permutation([], []).
permutation(L, [X | P]) :-
  del(X, L, L1),
  permutation(L1, P).

reverse([],[]).
reverse([E|T], R):-
  reverse(T,X),
  concat(X,[E],R).

%palindrome(L, ).
palindrome(L):-
  same(L,X),
  reverse(L, NL),
  same(X, NL).
