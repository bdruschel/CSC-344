/*
 * Brandon Druschel
 * Assignment #3: Minesweeper
 * Due Date: 11/21/16
 *
 * Description: 
 * ms.pl Attempts to create a minesweeper game that can be plauyed within a 
 * command line interface. The command 'play' begins the game.
 *
 * As of right now, 'display_board' is the only rule that is completely functional,
 * the rest of the program is incomplete.
 * 
 * Runnable Sample Code borrowed from Professor Odendahl:
 * http://cs.oswego.edu/~odendahl/coursework/csc344/201609/assignments/03.html
 *
 * viewTab and printList rules borrowed from:
 * http://stackoverflow.com/questions/32968553/print-list-of-lists-prolog
 */
 
% renamed to 'auxwin' since 'aux' is a forbidden file name in Windows
:- consult('auxwin').

:- dynamic board/2.
:- op(900, yfx, <-).
Suf <- N :-
   (N == 1 -> Suf = 'st'; N == 2 -> Suf = 'nd';
    N == 3 -> Suf = 'rd'; Suf = 'th').

% checked(' ').
% unchecked('.').
mark('_').

checked(X, Y) :-
   located_at(visible,X,Y,B), (mark(B); number(B)).

unchecked(X, Y) :-
   \+ checked(X,Y).

bomb('b').
filter(_, [], []).
filter(P, [A |As], Cs) :-
    (
       call(P, A) -> B = [A]
    ;
       B = []
    )
    , filter(P, As, Bs), append(B, Bs, Cs).

maxX(10).
maxY(10).
legit([A,B]) :-
   maxX(MaxX), maxY(MaxY),
   1 =< A, A =< MaxX, 1 =< B, B =< MaxY.

board(visible,
[
   ['.', '.', '.', '.', '.', '.', '.', '.', '.', '.'],
   ['.', '.', '.', '.', '.', '.', '.', '.', '.', '.'],
   ['.', '.', '.', '.', '.', '.', '.', '.', '.', '.'],
   ['.', '.', '.', '.', '.', '.', '.', '.', '.', '.'],
   ['.', '.', '.', '.', '.', '.', '.', '.', '.', '.'],
   ['.', '.', '.', '.', '.', '.', '.', '.', '.', '.'],
   ['.', '.', '.', '.', '.', '.', '.', '.', '.', '.'],
   ['.', '.', '.', '.', '.', '.', '.', '.', '.', '.'],
   ['.', '.', '.', '.', '.', '.', '.', '.', '.', '.'],
   ['.', '.', '.', '.', '.', '.', '.', '.', '.', '.']
]).

board(hidden,
[
   ['.', '.', '.', '.', '.', '.', '.', '.', '.', '.'],
   ['.', '.', '.', '.', '.', '.', '.', '.', '.', '.'],
   ['.', '.', 'b', '.', '.', '.', '.', '.', '.', '.'],
   ['.', '.', 'b', '.', 'b', '.', 'b', '.', '.', '.'],
   ['.', '.', '.', '.', '.', '.', '.', '.', '.', '.'],
   ['.', '.', '.', '.', 'b', '.', '.', '.', '.', '.'],
   ['.', '.', '.', '.', '.', '.', '.', '.', '.', '.'],
   ['b', 'b', '.', '.', '.', '.', '.', '.', '.', '.'],
   ['.', '.', '.', '.', '.', '.', '.', '.', '.', '.'],
   ['.', '.', '.', '.', '.', '.', '.', '.', '.', '.']
]).

% allows contents of grid to be printed without brackets/commas
viewTab([]).
viewTab([H|T]) :-
    printGrid(H),
    viewTab(T).

% print contents of a grid
printGrid([]) :-
    nl.
printGrid([H|T]) :-
    write(H),
    write(" "),
    printGrid(T).

:- style_check(-singleton).
% display the board specified by Which
display_board(Which) :-
   board(Which, X),
   viewTab(X).
:- style_check(+singleton).

:- style_check(-singleton).
% returns character at location X,Y
located_at(Which, X, Y, C) :-
   write('should show what is located at ['),
   write(X), write(','), write(Y), write('] on board \''),
   write(Which), write('\''), nl.
   %board(Which, Z),
:- style_check(+singleton).

:- style_check(-singleton).
/*
 * place_at(+Which, +X, +Y, +Char)
 * Which is visible or hidden
 */
place_at(Which,X,Y,Char) :-
   write('should place '), write(Char), write(' at ['),
   write(X), write(','), write(Y), write('] on board '),
   write(Which), nl.
:- style_check(+singleton).

retrieve(Prompt, Term) :-
   repeat,
      (
      write(Prompt),
      read_sentence(Sentence),
      % write_sentence(Sentence), nl,
      butlast(Sentence, Sentenc),
      % write(Sentenc), nl,
      phrase(sentence(Loc), Sentenc, []),
         (
         Loc == 'quit', write('quitting ...'), abort
         ;
         Term = Loc % note: in form [X, Y]
         )
      )
   .

play :-
   play(0).

play(M) :-
   N is M + 1,
   Suf <- N,
   display_board(visible), nl,
   format("Your ~d~a move~n", [N,Suf]),
   retrieve('Coordinates? ', [A,B]),
   format("DEBUG: probing at coordinates [~d,~d]~n", [A, B]),
   !, probe(A,B),
   play(N).

/*
 * Be able to do this on exam 2
 */
count(_, [], 0).
count(X, [X|Ys], Z) :- count(X, Ys, W), Z is 1+W.
count(X, [_|Ys], W) :- count(X, Ys, W).

neighbors(X, Y, Nbrs) :-
   NWX is X-1, NWY is Y-1,
   NEX is X-1, NEY is Y+1,
   WX  is X,   WY  is Y-1,
   EX  is X,   EY  is Y+1,
   SWX is X+1, SWY is Y-1,
   SEX is X+1, SEY is Y+1,
   NX is X-1, NY is Y,
   SX is X+1, SY is Y,

   Nbrs_unfiltered =
   [[NWX, NWY],
    [NEX, NEY],
    [WX,  WY],
    [EX,  EY],
    [SWX, SWY],
    [SEX, SEY],
    [NX,  NY],
    [SX,  SY]],
   filter(legit, Nbrs_unfiltered, Nbrs).

:- style_check(-singleton).
has_bomb(X,Y) :-
   write('should evaluate to true if a bomb is at ['),
   write(X), write(','), write(Y), write('] on hidden board '),
   nl.

bomb_count([X, Y], Count) :-
   write('should return 0 or 1, i.e., the number of bombs at ['),
   write(X), write(','), write(Y), write('] on hidden board '),
   nl.
   
bomb_count_neighbors([X, Y], Count) :-
   write('should return the number of bombs adjacent to ['),
   write(X), write(','), write(Y), write('] on hidden board '),
   nl.

expose([X, Y]) :-
   write('should expose on visible board what is '),
   write('at ['),
   write(X), write(','), write(Y), write('] on hidden board '),
   nl.
   
explode(X,Y) :-
   write('should explode on visible board '),
   write('at ['),
   write(X), write(','), write(Y), write(']'), nl.

probe(X, Y) :-
   write('should probe '),
   write('at ['),
   write(X), write(','), write(Y), write(']'), nl.
:- style_check(+singleton).

