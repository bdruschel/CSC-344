-- |  Brandon Druschel
-- |  Assignment 4b: dup
-- |  Due Date: 12/8/16
-- The function 'dup' iterates through a input string 's'
-- and duplicates every instance of the input char 'c'.
--
-- The main exists only for testing purposes. 
--
-- The concatMap idea was borrowed from this page:
-- https://goo.gl/lVhC13
--
-- Input: dup [Char] [String]
-- Output: String with the given char duplicated.

module Main where
   dup :: Char -> [Char] -> [Char]
   dup c s = concatMap(\x -> if x == c then (replicate 2) x else [x]) s

   main = do
      let x = dup 's' "This is serious business!"
      putStrLn $ show $ x
      let y = dup 'C' "CAPS LOCK IS CRUISE CONTROL FOR COOL"
      putStrLn $ show $ y
      let z = dup 'p' "I'm a people pleaser."
      putStrLn $ show $ z