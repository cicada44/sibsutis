(defun union-sets (set1 set2)
  (cond
    ((null set1) set2)              ; Если set1 пусто, возвращаем set2
    ((member (car set1) set2)       ; Если текущий элемент set1 уже есть в set2, рекурсивно обрабатываем остальные элементы set1
     (union-sets (cdr set1) set2))
    (t                            ; В противном случае, добавляем текущий элемент set1 к результату и рекурсивно обрабатываем остальные элементы обоих множеств
     (cons (car set1) (union-sets (cdr set1) set2)))))

; Проверка работы функции объединения множеств
(let ((set1 '(1 2 3))
      (set2 '(2 3 4)))
  (setq result (union-sets set1 set2))
  (print result))
(let ((set1 '(1))
      (set2 '(2)))
  (setq result (union-sets set1 set2))
  (print result))
  
