main = do
  a <- getInt
  b <- getInt
  let l = filter (>= a) $ takeWhile (<= b) primes 
  putStrLn $ show $ interval l 0 

-- interval of an empty or single element list returns n
-- else, get the max between the difference of first two elements and the recursive call on list tail
interval [] n = n
interval [x] n = n
interval (x:xs) n = max (head xs - x) (interval xs n)

primes = sieve [2..]

sieve (p:xs) = p : sieve [x| x <- xs, x `mod` p > 0]

getInt :: IO Int 
getInt = read <$> getLine

