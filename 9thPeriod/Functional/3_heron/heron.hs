main = do
  a <- getInt
  b <- getInt
  c <- getInt
  putStrLn $ area [a, b, c]

area sides
  | not (check_triangle sides 3) = "-"
  | otherwise = show $ sqrt (p * (p - a) * (p - b) * (p - c)) 
    where 
      a = sides!!0
      b = sides!!1
      c = sides!!2
      p = (a + b + c) / 2

check_triangle _ 0 = True
check_triangle list n
  | (list!!0 + list!!1 >= list!!2) = check_triangle (rotate list) (n-1)
  | otherwise = False

rotate (x:xs) = xs ++ [x]

getInt :: IO Double
getInt = read <$> getLine
