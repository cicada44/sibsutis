(defun replace-if-not (predicate lst)
  (if (null lst)
      nil
      (let ((new-head (if (funcall predicate (car lst)) (car lst) '*)))
        (cons new-head (replace-if-not predicate (cdr lst))))))

; Проверка работы функционала замены элементов
(let ((my-list '(1 2 3 "four" 5 "six")))
  (setq result (replace-if-not 'numberp my-list))
  (print result))

(let ((my-list '(1 -2 3 -4 5 -6)))
  (setq result (replace-if-not (lambda (x) (> x 0)) my-list))
  (print result))
