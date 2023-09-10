(defun is-subset (set1 set2)
  (cond
    ((null set1) t)                ; Пустое множество всегда подмножество
    ((null set2) nil)              ; Если set2 пусто, set1 не может быть подмножеством
    ((member (car set1) set2)      ; Если текущий элемент set1 есть в set2, рекурсивно проверяем остальные элементы
     (is-subset (cdr set1) set2))
    (t nil)))                      ; Если ни одно из вышеперечисленных условий не выполняется

; Проверка работы предиката
(let ((set1 '(2 3))
      (set2 '(2 3 4)))
  (if (is-subset set1 set2)
      (print "set1 является подмножеством set2")
      (print "set1 не является подмножеством set2")))

(let ((set3 '(1 2 3))
      (set4 '(2 3 4)))
  (if (is-subset set1 set2)
      (print "set3 является подмножеством set4")
      (print "set4 не является подмножеством set4")))
