main = do
  putStrLn $ show $ sumList [1,2,3,-5]
  putStrLn $ show $ [1,2,3,-5]

sumList [] = 0
sumList (x:xs)
 | x < 0 = sumList xs
 | otherwise = x + sumList xs
