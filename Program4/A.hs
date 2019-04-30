-- |  Brandon Druschel
-- |  Assignment 4a: irepeat
-- |  Due Date: 12/8/16
-- The function 'irepeat' Applies a function 'x' to an element 'y'
-- a certain 'n' amount of times. doubleMe, brokenRecord, and
-- fac are all simple functions used for testing irepeat.
--
-- 'iterate' was used to generate an infinite list of recursively-
-- -applied functions. irepeat simply takes the n'th result from
-- that list. This idea was borrowed from the following page:
-- http://stackoverflow.com/questions/7423123/how-to-call-the-same-function-n-times
--
-- Input: irepeat [function] [element] [Int]
-- Output: Final element result.

module A (doubleMe, brokenRecord, fac, irepeat) where
   doubleMe :: Num a => a -> a
   doubleMe x = x + x
   
   brokenRecord :: [a] -> [a]
   brokenRecord x = x ++ x
   
   fac 0 = 1
   fac n = n * fac (n-1)
   
   irepeat :: (a -> a) -> a -> Int -> a
   irepeat x y n = (iterate x y) !! n