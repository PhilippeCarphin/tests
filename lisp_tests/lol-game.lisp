(defun reload ()
  (load (compile-file "lol-game.lisp")))

(defparameter *nodes* '((living-room (you are in the living room))
                        (garden (you are in a bueautiful garden.  There is a well in front of you))
                        (attic  (you are in the attic.  There is a giant welding torch in the corner.))))

;; For something to show up when we run the file, but we should use the REPL
(print (assoc 'garden *nodes*))

(defparameter *edges* '((living-room (garden west ladder))
                        (garden (living-room east door))
                        (attic (living-room downstairs ladder))))

(defun describe-path (edge)
  `(there is a ,(caddr edge) going ,(cadr edge) from here '(here being ,(car edge))))


(print (describe-path '(garden west door)))


