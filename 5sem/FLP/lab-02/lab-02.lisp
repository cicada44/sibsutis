(defun double-list (lst)
  (cond
    ((null lst) nil)
    (T (append (list (car lst) (car lst))
              (double-list (cdr lst))))))



(defun get-pairs (lst)
  (cond
    ((null lst) nil)
    ((null (cdr lst)) (list (car lst)))
    (t (cons(list (car lst) (car (last lst)))
	    (get-pairs (cdr (butlast lst))))))
  )

(defun remove-elements (lst indices &optional (current-index 1))
  (cond
    ((null lst) nil)
    ((null indices) lst)
    ((= current-index (car indices))
     (remove-elements (cdr lst) (cdr indices) (1+ current-index)))
    (t
     (cons (car lst) (remove-elements (cdr lst) indices (1+ current-index)))))
)