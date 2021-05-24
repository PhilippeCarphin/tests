(require '[clojure.java.shell :as shell])
(println (:out (shell/sh "/bin/echo" "Printing a command-line output")))
;; I haven't looked into it but for some reason when I call an external
;; command, I need to add this call to System/exit otherwise the program
;; hangs at the end.

;; The obvious thing to look into would be that we are waiting for a child
;; process.
;;
;; I found that adding an exit call would make the program exit
;;
;;    (System/exit 0)
;;
;; But further reading https://clojureverse.org/t/why-doesnt-my-program-exit/3754/2
;;
;; Showed that you're supposed to shudown:
;;
;; https://clojureverse.org/t/why-doesnt-my-program-exit/3754/8
;; ============================================================
;;   The use of shutdown-agents isn’t a workaround, but the intended normal use.
;;   The issue here is sh doc-string not mentioning its usage of the agent pool.
(shutdown-agents)
