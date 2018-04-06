-- ====================== fizz_buzz_1 =========================================
buzz_1 = \a -> if mod a 5 == 0 then "buzz" else ""
fizz_1 = \a b -> if mod a 3 == 0 then "fizz" ++ b else b
fizz_buzz_1 = \n -> if fizz_1 n (buzz_1 n) == ""
                    then show n
                    else fizz_1 n (buzz_1 n)

-- ====================== fizz_buzz_2 =========================================
fizz_buzz_2 n = fizz ++ buzz ++ string
                where
                    fizz = if mod n 3 == 0 then "fizz" else ""
                    buzz = if mod n 5 == 0 then "buzz" else ""
                    string = if (fizz == "" && buzz == "") then show n else ""

-- ====================== fizz_buzz_3 =========================================
true = \x y -> x
false = \x y -> y
fizz = \n -> if mod n 3 == 0 then true else false
buzz = \n -> if mod n 5 == 0 then true else false
number = \n -> if (mod n 3 /= 0 && mod n 5 /= 0) then true else false
fizz_buzz_3 n = (fizz n) "fizz" "" ++  (buzz n) "buzz" "" ++ (number n) (show n) ""

-- ====================== fizz_buzz_4 =========================================
fizz_buzz_4 = \n -> fizz n (buzz n "fizzbuzz" "fizz") (buzz n "buzz" (show n))

-- ====================== fizz_buzz_5 =========================================
-- Starting to just use the idea that booleans are selectors
-- so a function 
divisible_lc a n = \x y -> if mod a n == 0 then x else y
fizz_buzz_5 = \n -> divisible_lc n 3 (divisible_lc n 5 "fizzbuzz" "fizz") (divisible_lc n 5 "buzz" (show n))

-- ====================== fizz_buzz_6 =========================================
fizz_lc n = \x y -> divisible_lc n 3 x y
buzz_lc n = \x y -> divisible_lc n 5 x y
fizz_buzz_6 = \n -> fizz_lc n (buzz n "fizzbuzz" "fizz") (buzz_lc n "buzz" (show n))

not_lc = \x -> x false true
and_lc = \x y -> x y false

number_lc n = \x y -> and_lc (not_lc (fizz_lc n)) (not_lc (buzz_lc n)) x y

fizz_buzz_7 = \n -> number_lc n
                            (show n)
                            (fizz_lc n "fizz" "" ++ buzz_lc n "buzz" "")

fizz_buzz = \n -> fizz_buzz_7 n

main = do
    putStrLn "Fizzbuzz program"
    putStrLn (fizz_buzz 1)
    putStrLn (fizz_buzz 2)
    putStrLn (fizz_buzz 3)
    putStrLn (fizz_buzz 4)
    putStrLn (fizz_buzz 5)
    putStrLn (fizz_buzz 6)
    putStrLn (fizz_buzz 7)
    putStrLn "..."
    putStrLn (fizz_buzz 13)
    putStrLn (fizz_buzz 14)
    putStrLn (fizz_buzz 15)
