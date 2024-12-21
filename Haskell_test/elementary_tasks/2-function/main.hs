

add :: Integer -> Integer -> Integer
add x y = x+y

greet :: [Char] -> [Char]
greet person = "Hello " ++ person

main = do
    let a = add 5 9
    print a
    -- I tried real hard to make the function print but I couldn't do it
    -- I guess this is normal since printing would be a side effect so
    let b = greet "phil"
    print b


