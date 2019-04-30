% File:  auxwin.pl
%      - just some auxiliary predicates
%      - "aux.pl" had to be renamed to 'auxwin.pl,' since 'aux' is a forbidden file name in Windows
:- consult('grammar').
:- consult('io').

butlast([_],[]).
butlast([X|Xs],[X|Ys]) :-
  butlast(Xs,Ys).

doit(F) :-
   seeing(Keyboard),
   see(F),
   proc,
   see(Keyboard).

