true   = \x y -> x
false  = \x y -> y

not_op = \b   -> b false true
and_op = \x y -> x y false -- if x is false, return false without checking y, otherwise return whatever y is.
or_op  = \x y -> x true y -- if x is true, return true without checking y, otherwise, return whatever y is.

main = do
    putStrLn ("true  = " ++ true  "true" "false") -- true  is the function that selects the first  of it's arguments
    putStrLn ("false = " ++ false "true" "false") -- false is the function that selects the second of it's arguments
    putStrLn "======== NOT ========"
    -- not_op true is the function that selects the second of it's arguments, so -- not_op true is false
    putStrLn ("not_op true  = "       ++ (not_op true)        "true" "false")
    -- not_op false is the function that selects the first of it's arguments, so not_op false is true
    putStrLn ("not_op false = "       ++ (not_op false)       "true" "false")
    -- and so on ...
    putStrLn "======== AND ========"
    putStrLn ("not_op false = "       ++ (not_op false)       "true" "false")
    putStrLn ("and_op false false = " ++ (and_op false false) "true" "false")
    putStrLn ("and_op false true  = " ++ (and_op false true)  "true" "false")
    putStrLn ("and_op true  false = " ++ (and_op true false)  "true" "false")
    putStrLn ("and_op true  true  = " ++ (and_op true true)   "true" "false")
    putStrLn "======== OR ========= "
    putStrLn ("or_op  false false = " ++ (or_op false false)  "true" "false")
    putStrLn ("or_op  false true  = " ++ (or_op false true)   "true" "false")
    putStrLn ("or_op  true  false = " ++ (or_op true false)   "true" "false")
    putStrLn ("or_op  true  true  = " ++ (or_op true true)    "true" "false")





