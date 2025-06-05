-- Alexandre Brito Gomes 11857323
-- Gabriel Victor Cardoso Fernandes - 11878296
-- Vítor Amorim Fróis - 12543440

import System.IO
import Debug.Trace
import Data.Ord
import Data.List
import Data.Maybe

import Data.Maybe (fromMaybe)

main = do
  line <- getLine
  file <- openFile "dados.csv" ReadMode
  contents <- hGetContents file
  let countryList = processCountry $ lines contents
  let numbers = map (read::[Char]->Int) (splitOnChar ' ' line)
  
  -- Soma de Active de todos paises com Confirmed >= n1
  putStrLn $ 
    show $
    sum $ 
    map active $
    filter ((>=numbers!!0).confirmed) $
    countryList
  -- Dentre os n2 paises com maiores valores de active, a soma das deaths dos n3 paises com menores valores de confirmed
  putStrLn $
    show $
    sum $
    map deaths $
    take (numbers!!2) $
    sortBy (comparing confirmed) $
    take (numbers!!1) $
    sortBy (flip (comparing active)) $
    countryList
  -- Os n4 paises com maiores valores de confirmed em ordem alfabetica
  mapM_ putStrLn $
    sort $
    map name $
    take (numbers!!3) $
    sortBy (flip (comparing confirmed)) $
    countryList


data Country = Country {
  name :: [Char], 
  confirmed :: Int, 
  deaths :: Int, 
  recovery :: Int, 
  active :: Int 
} deriving (Show, Read)
nullCountry = Country " " 0 0 0 0

convertCountry :: [String] -> Maybe Country 
convertCountry (name:confirmed:deaths:recovery:active:[]) = 
  Just $ Country 
    (name)
    (read confirmed)
    (read deaths)
    (read recovery)
    (read active)
convertCountry _ = Nothing

processCountry :: [String] -> [Country]
processCountry [] = []
processCountry (x:xs) =
  [fromMaybe nullCountry country] ++ processCountry xs
  where
    country = convertCountry $ splitOnChar ',' x

splitOnChar :: Char -> String -> [String]
splitOnChar _ [] = [""]
splitOnChar delim (c:cs)
    | c == delim = "" : rest
    | otherwise  = (c : head rest) : tail rest
  where
    rest = splitOnChar delim cs

