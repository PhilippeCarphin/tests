;; A function that shows some lisp syntax
;; A function definition
(defun say-hello (world)
  ;; Create local variables inside a let.  It takes a list of 2-element lists
  ;; where the first element is the variable and the second is it's value.
  (let ((message (concatenate 'string "Hello " world "!")))
    ;; Now we're doing a for loop iterating over message as a list of chars
    (loop :for l :across message :collect l)))

;; Testing it out
;; Calculating the result
(let ((result (say-hello "world")))
  ;; Printing the result as a list of chars
  (print result)
  ;; Re-concatenating the chars to form the string
  (print (concatenate 'string result)))

