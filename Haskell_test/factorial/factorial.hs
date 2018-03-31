factorial n = if n == 0 then 1 else n * factorial (n - 1)

main = do
    print ( factorial 7 )
    putStrLn ( "HELLO" )
    my_function
    my_other_function
    print "end of main"
    print (add 5 7)

my_function = putStrLn ( "phil" )

add a b = a + b

my_other_function = do
    putStrLn("  other")
    putStrLn("hello")
