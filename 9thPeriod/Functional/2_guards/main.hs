main = do
  putStrLn $ show $ signal $ -17

signal x
 | x < 0 = -1
 | x == 0 = 0
 | x > 0 = 1
