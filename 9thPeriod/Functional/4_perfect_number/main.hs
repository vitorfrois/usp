main = do
  a <- getInt
  b <- getInt
  putStrLn $ show $ count a b defective
  putStrLn $ show $ count a b perfect
  putStrLn $ show $ count a b abundant


-- counts the number of f(i) for i in [a,b]
count a b f = sum [1 | i <- [a..b], f i]

-- I got the first example from Stack Overflow, so I will translate 
-- how I would read the function in human language
-- perfect is a function of n that returns true if
-- the sum of a list of i where i goes from 1 to n-1 
-- and i is a divisor of n, equals n itself
-- else, it returns false

perfect n = n == sum [i | i <- [1..n-1], n `mod` i == 0]
abundant n = n < sum [i | i <- [1..n-1], n `mod` i == 0]
defective n = n > sum [i | i <- [1..n-1], n `mod` i == 0]

getInt :: IO Integer
getInt = read <$> getLine

