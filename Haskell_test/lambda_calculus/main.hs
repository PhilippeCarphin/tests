-- DOWNLOAD : https://www.haskell.org/platform/
-- BUILD : See Makefile
-- true : λx.λy.y
true  = \x y -> x
-- false: λx.λy.x
false = \x y -> y

not_op = \b   -> b false true
-- a compléter, remplacer "true" par la réponse --
and_op = \x y -> true -- hint : if x is false, return false without checking y, otherwise return whatever y is.
or_op  = \x y -> true -- hint : if x is true, return true without checking y, otherwise, return whatever y is.


-- Lambda calculus-y definition of the integer
-- http://www.dmi.unict.it/~barba/LinguaggiII.html/READING_MATERIAL/LAMBDACALCULUS/LAMBDACALCULUS.1.HTM
-- Take a function i and apply it zero times to x
zero = \i x -> x
-- Apply i once
one = \i x -> i x
-- apply i to the result of applying i once
two = \i x -> i (i x)
-- and so on
three = \i x -> i (i (i x))

-- if number applies i to x multiple times,
-- number + 1 applies i to x number times,
-- and applies i to the result of that, thus
-- applying i one more time.
incr = \number -> \i x -> i (number i x)
num 0 = \i x -> x
num n = incr(num(n-1))
main = do
    -- true  is the function that selects the first  of it's arguments
    putStrLn ("true  = " ++ true  "true" "false")
     -- false is the function that selects the second of it's arguments`
    putStrLn ("false = " ++ false "true" "false")
    -- you can tell whether a function is true or false by calling it with the
    -- arguments "true" "false" because if said function is true, it will selects
    -- the first argument and if it is false it will select the second
    putStrLn "======== NOT ========"
    -- not_op true is the function that selects the second of it's arguments, so -- not_op true is false
    putStrLn ("not_op true  = "       ++ (not_op true)        "true" "false")
    -- not_op false is the function that selects the first of it's arguments, so not_op false is true
    putStrLn ("not_op false = "       ++ (not_op false)       "true" "false")
    -- and so on ...
    putStrLn "======== AND ========"
    putStrLn ("and_op false false = " ++ (and_op false false) "true" "false")
    putStrLn ("and_op false true  = " ++ (and_op false true)  "true" "false")
    putStrLn ("and_op true  false = " ++ (and_op true false)  "true" "false")
    putStrLn ("and_op true  true  = " ++ (and_op true true)   "true" "false")
    putStrLn "======== OR ========= "
    putStrLn ("or_op  false false = " ++ (or_op false false)  "true" "false")
    putStrLn ("or_op  false true  = " ++ (or_op false true)   "true" "false")
    putStrLn ("or_op  true  false = " ++ (or_op true false)   "true" "false")
    putStrLn ("or_op  true  true  = " ++ (or_op true true)    "true" "false")

    putStrLn "==== Natural numbers= "
    print (zero                (\n->n+1) 0) -- apply the arithmetic increment zero times to 0
    print (one                 (\n->n+1) 0) -- apply the arithmetic increment one time to 0
    print (two                 (\n->n+1) 0) -- and so on
    print (three               (\n->n+1) 0)
    putStrLn "===== Increment ===== "
    print ((incr three)        (\n->n+1) 0) -- apply the arithmetic increment (incr three) times to 0
    print ((incr (incr three)) (\n->n+1) 0)
    putStrLn "==== Recursive def=== "
    print ((num 7)             (\n->n+1) 0)
    print ((num 88)            (\n->n+1) 0)
    print ((num 9999)          (\n->n+1) 0)
