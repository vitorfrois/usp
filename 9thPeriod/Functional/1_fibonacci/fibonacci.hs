main = do
	putStrLn $ show $ result $ 5

result 0 = 1
result 1 = 1
result x = result (x - 1) + result (x - 2)
