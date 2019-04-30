/*
 * Brandon Druschel
 * Assignment #3: Minesweeper
 * Due Date: 11/21/16
 *
 * Sample grammar.pl borowed from Odendahl:
 * http://cs.oswego.edu/~odendahl/coursework/csc344/201609/assignments/03/grammar.txt
 *
 */

sentence(quit) --> [quit].
sentence([X, Y]) --> [probe], [X], [Y], {number(X), number(Y)}.

