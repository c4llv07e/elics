module Main where

type Line = String
type Text = [Line]

data Editor = Editor { scrPos  :: Int
                     , scrSize :: Int
                     }

stringToText :: String -> Text
stringToText str = case dropWhile cond str of
                     ""   -> []
                     str' -> line : stringToText strTail
                       where (line, strTail) = break cond str'
                   where cond = (== '\n')

showText :: Text -> IO ()
showText [] = return ()
showText text = do
  putStrLn $ head text
  showText $ tail text

startupEditor :: Editor
startupEditor = Editor { scrPos  = 0
                       , scrSize = 10
                       }

initEditor :: IO (Editor)
initEditor = return startupEditor

fragment :: (Int, Int) -> [a] -> [a]
fragment (start, end) arr
  | start >= end = []
  | length arr <= start = []
  | otherwise = arr!!start : fragment ((start + 1), end) arr

addLineNumber :: Int -> Text -> Text
addLineNumber _ [] = []
addLineNumber num (x:xs) = ((show num) ++ (' ' : x)) : addLineNumber (num + 1) xs

addLineNumbers :: Text -> Text
addLineNumbers = addLineNumber 1

editorLoop :: Editor -> IO ()
editorLoop editor = do
  let raw = "All\nYour\nBase\nAre\nBelong\nTo\nUs"
  let rawText = stringToText raw
  let frag = fragment fragVal rawText
  let text = addLineNumber ((fst fragVal) + 1) frag
  showText text
  if True then return () else editorLoop editor
  where
    fragVal = (scrPos editor, (scrPos editor) + scrSize editor)

main :: IO ()
main = do
  editor <- initEditor
  editorLoop editor
