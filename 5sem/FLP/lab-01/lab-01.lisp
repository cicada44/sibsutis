(defun task1 (myset)
  (cdr (cdr (car (car (cdr myset)))))
)

#|
list creates a list of the following elements:
1. `(a b) is a list containing elements a and b.
2. 7 is just a number.
3. '(()) is a list containing a single element - an empty list ().

Return value: ((A B) 7 (NIL))
|#
(defun task2 ()
  (list '(a b) 7 '(()))
)

(defun task3cons ()
  (cons 1 (cons `(2) (cons 3 nil)))
)

(defun task3list ()
  (list 1 (list 2) 3)
  ;(list 1 `(2) 3)
)


(defun task4 (myset)
  (append (list (car (cdr myset)) (car myset)) (cdr (cdr myset)))
)
