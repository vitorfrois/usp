main = do
 putStrLn $ show $ baskara 1 1 0

baskara a b c
 | delta < 0 = []
 | delta == 0 = [x]
 | otherwise = [x1, x2]
   where 
     delta = b ^ 2 - (4 * a * c)
     x = (-b) / (2 * a)
     x1 = (-b + sqrt delta) / (2 * a)
     x2 = (-b - sqrt delta) / (2 * a)
