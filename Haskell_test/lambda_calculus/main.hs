-- DOWNLOAD : https://www.haskell.org/platform/
-- BUILD : See Makefile
-- We start by defining the constants "true" and "false".
-- Since all we have are functions, they need to be defined as functions.  they
-- will both be functions that take two arguments and return one of them.  In an
-- arbitrary choice, we decide that "true" is the function that returns its first
-- argument and false is the function that returns its second argument.

-- true : λx.λy.y
true  = \x y -> x

-- false: λx.λy.x
false = \x y -> y

-- Given a fucntion f that is one of these two functions, we can know which once
-- it is by passing it the the strings "true" and "false" and printing the result
-- of the evaluation. f "true" "false" will return the string "true" if f is the
-- function true, and "false" if f is the function "false".

-- Let 'b' be one of these two functions, we can construct the 'negation' operation
-- which takes 'b' and returns one of the true or false functions, the one that
-- 'b' isn't.  The operation not_op evaluates 'b' with the arguments false true
-- and we can see that if 'b' is true, the result of 'b false true' will be false
-- and if b is false, the result of 'b false true' will be true.
not_op = \b -> b false true


-- Following this logic, we can do the 'and' and 'or' operations by asking
-- what 'x' is.  Replace 'true' by something
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
