order_of_eliminations(N, M, ResultedList) :-
    M > 0,
    numlist(1, N, Xs),
    order_of_eliminations(Xs, Xs, 1, M, ResultedList).
 
order_of_eliminations([], [], _, _, []).

order_of_eliminations([], [X0 | Xs0], N, M, ResultedList) :-
    !,
    order_of_eliminations([X0 | Xs0], [X0 | Xs0], N, M, ResultedList).

order_of_eliminations([X | Xs], Xs0, M, M, [X | ResultedList]) :-
    append(Xs1, [X | Xs], Xs0),
    append(Xs, Xs1, Xs2),
    !,
    order_of_eliminations(Xs2, Xs2, 1, M, ResultedList).

order_of_eliminations([_ | Xs], Xs0, N, M, ResultedList) :-
    N1 is N + 1,
    order_of_eliminations(Xs, Xs0, N1, M, ResultedList).
