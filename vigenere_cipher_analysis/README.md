# Vigenère cipher analysis

Cryptoanalysis consists of two parts:
1. Key length examination
    * Kasiski test ([wiki](https://en.wikipedia.org/wiki/Kasiski_examination))
    * Friedman test ([wiki](https://en.wikipedia.org/wiki/Friedman_test))
2. Statistical attack

[Preview](http://htmlpreview.github.io/?https://github.com/yawnkim/archive/blob/master/vigenere_cipher_analysis/index.html)

## Overview
We are given a ciphertext encrypted with Vigenère cipher.
Original plaintext is written in polish language (thought it can include some foreight words).
Neither plaintext nor ciphertext include any punctuation.
Both are written in lowercase-only basic Latin alphabet that consists of 26 letters.

## Key length examination
During the first phase we need to determine the length of the key.

Kasiski test looks for repeated substrings (of length >= 3) in a ciphertext.
Distances (number of chars) between these occurences are likely to be the multiples of the key-length.
Thus GCD of all these distances is chosen in result.

For the Friedman test we use Polish language Index of coincidence PL_IC = 0.052967681.
Then we have an iteration.
For each i (from 1 to 16 or less if ciphertext is shorter than that) we 'shift' the text.
One can think of it as placing a text characters in a matrix of i-columns and then calculating each column's index of coincidence IC.
Afterwards we take the their average IC and use it for calculating difference between it and the PL_IC.
The least delta IC's shift value i is chosen in result.

Sometimes these two tests might produce different results. (Both are tested separately then)

## Statistical attack
Assume that the value for key length from the first step = |K|.
We then take |K| chunks of text (basically we 'break' text into |K| blocks).
Chunk of index i=1...|K| is a concatenation of every |K|-th letter starting from i.
We can say that each chunk is encrypted with monoalphabetic 1-letter cipher.
To find that 1-char key in each chunk we:
* try decrypting the text-chunk with 1-letter key (26 option) and calculate every characters frequency
* choose the letter that produces closest (in terms of root mean square) to 'polish language character frequency table' result

#### Average letter frequency in a Polish language text
| char | avg freq |
|------|---------:|
| a | 100 |
| b | 15 |
| c | 37 |
| d | 34 |
| e | 90 |
| f | 1 |
| g | 15 |
| h | 12 |
| i | 88 |
| j | 27 |
| k | 35 |
| l | 37 |
| m | 31 |
| n | 55 |
| o | 79 |
| p | 25 |
| q | 0 |
| r | 38 |
| s | 55 |
| t | 39 |
| u | 22 |
| v | 0 |
| w | 46 |
| x | 0 |
| y | 43 |
| z | 65 |


Finally, concat these 1-letter keys (in total of |K|) into result and in additional display decrypted raw text.
