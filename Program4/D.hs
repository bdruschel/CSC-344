-- |  Brandon Druschel
-- |  Assignment 4d: factors
-- |  Due Date: 12/8/16 
-- The function 'factors' takes an Int 'n' and returns a list of
-- all of the Int's prime factors. 
--
-- The algorithm for generating the list of factors was borrowed from here:
-- http://stackoverflow.com/questions/21276844/prime-factors-in-haskell
--
-- Input: factors [Int]
-- Output: List of factors that apply to the given Int.

module D (can_divide, factors) where
   -- Can the number be evenly divided by n? 
   can_divide :: Int -> Int -> Bool
   -- can_divide n1 n2 = n1/n2 == fromInteger (round(n1/n2))
      -- It turns out that you cannot use the '/' operator for Int's. 
      -- 'div' cannot return a float, so 'mod' is used instead
   can_divide n1 n2 = (n1 `mod` n2) == 0
   
   factors :: Int -> [Int]
   factors 0 = []
   factors 1 = []
   factors n
      | f == [] = [n]
      | otherwise = f ++ factors (div n (head f))
      where f = take 1 $ filter (\x -> (can_divide n x) == True) [2 .. n-1]