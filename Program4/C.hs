-- |  Brandon Druschel
-- |  Assignment 4c: replace
-- |  Due Date: 12/8/16    
-- The function 'replace' takes a list 'l' and replaces all of
-- the items from position 's1' through 's2' with an inputted list 'r'.
--
-- The main is taken directly from the Program #4 instructions
--
-- The idea of utilizing 'take' and 'drop' for the replace function
-- was borrowed from this source:
-- http://stackoverflow.com/questions/15530511/how-to-edit-nth-element-in-a-haskell-list
--
-- Input: replace [replacement list] ([pos 1], [pos 2]) [original list]
-- Output: Original list with indicated area replaced by another given list.


module Main where
   replace :: [a] -> (Int, Int) -> [a] -> [a]
   replace r (s1, s2) l = take s1 l ++ r ++ drop (s2+1) l
   
   main = do
      let x_orig = [100,200,300,400,500,600,700]
      let x_rep = replace [1,2,3] (4,5) x_orig
      putStrLn ("Original list: " ++ (show x_orig))
      putStrLn ("Replacement list: " ++ (show x_rep))
      let a = "a vote for me is a vote for the people"
      let b = length a
      let y = replace "big moneyed interests" (b-6,b-1) a
      putStrLn ("Original statement: " ++ a)
      putStrLn ("Replacement statement: " ++ (show y))
      
