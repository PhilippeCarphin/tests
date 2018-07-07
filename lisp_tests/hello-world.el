(defun say-hello (world)
  (concatenate 'string "Hello " world "!"))

(message (say-hello "world"))

