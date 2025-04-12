main = do 
  putStrLn $ show $ absoluto $ -10

absoluto x
 | x < 0 = -x
 | otherwise = x
