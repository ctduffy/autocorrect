# README #

Here is the command I use to compile and run this:

gcc -g -std=c99 linked.c trie.c autocorrect.c leven.c -o rt

Then, inside gdb, this function takes in 3 command-line arguments:
first: the name of the file to create the trie from
second: the word or part of the word that you want to correct or complete
third: an integer that represents the maximum edit distance that you want the function to return

So, to run it, I might do something like:

gdb ./rt

r wordsEn.txt aard 2

The function will then print out all words that are within an edit distance of two to "aard," as well as all possible completions of aard. 

###
Some constraints/extra tidbits:

-there are three text files in this repo: wordsfirst.txt, wordssecond.txt, and wordsEn.txt. wordsfirst.txt contains a little over 100 words, and only includes a and b words. wordssecond.txt contains almost 8000 words, also only including a and b words. wordsEn.txt contains all english words (excluding contractions), about 110,000 of them. However, none of these files include repeating words, because I didn't search the internet long enough to find a newline divided dictionary of many words in the english language.

-if you want to use this with your own file of words, it cannot (at the moment) contain any thing other than lowercase letters and newline characters.:) this is a place for improvement.

* Owned by: Clara Duffy
* contact Clara Duffy at ctduffy@college.harvard.edu with any questions, comments, or suggestions
