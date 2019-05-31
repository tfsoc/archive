# -*- coding: utf-8 -*-
import operator
import math

szyfrogram = """xmvwj dsldi torpv jolvq pkcec aeaem qvrak eprwg pnvky nmrwd btisz pvtny oecrs
            fhfas fpbsc dmkao hsbvy mijxg bmuss msjgs uafmm iqzec uyisc mescd xsaeg zdjdy
            tgeen ddcsg jibmo noksb zxron pfido asikk omqsg bpain osdmk txftk nmvgy ucdmm
            iarpk csgvk xsueg txnst fwkdb phciw essvy cckyv vhlxb xecit vgqgs xsjgs jwgsu
            pnlac ssuty ehrri dlemo teudo cckeu cccsc myjdx baphk kidmc jiido ddgvj fgzax
            bozin zrrpe edzwz bhrnk omvwj ddvwm jeemo qsbst bwzis cetdk oeksm ppvdi xmtls
            oxvvo tmveu jiuce acjoe kesij qmvgj fwkay qsqak meaec jijoe tmtdv vdvtc vgzys
            xcqfi xeaec jigsg tgzeq mmnsc dmaeu brrvj vgrgj vnesc dnroj fxiyn osfxy ccisj
            teuiu tdvhv xtrvj fdusl ssscd fqbxy scemo txvxi oeagj fwtmo ksufs fvrrk nvfde
            nmjtb bazej fsemw aegsw jrrqi""" \
            .replace(" ","").replace("\n","")
alphabet = {
  "a": 0,
  "b": 0,
  "c": 0,
  "d": 0,
  "e": 0,
  "f": 0,
  "g": 0,
  "h": 0,
  "i": 0,
  "j": 0,
  "k": 0,
  "l": 0,
  "m": 0,
  "n": 0,
  "o": 0,
  "p": 0,
  "q": 0,
  "r": 0,
  "s": 0,
  "t": 0,
  "u": 0,
  "v": 0,
  "w": 0,
  "x": 0,
  "y": 0,
  "z": 0
}

pl = {
    'a':100,
    'b':15,
    'c':37,
    'd':34,
    'e':90,
    'f':1,
    'g':15,
    'h':12,
    'i':88,
    'j':27,
    'k':35,
    'l':37,
    'm':31,
    'n':55,
    'o':79,
    'p':25,
    'q':0,
    'r':38,
    's':55,
    't':39,
    'u':22,
    'v':0,
    'w':46,
    'x':0,
    'y':43,
    'z':65
}


def divisorsOf(n):
    l = []
    for i in range(2,n+1):
        if n % i == 0:
            l.append(i)
    return l

def repeatsOf(txt):
    reps = set()
    diffmap = {}
    freq = []
    info = ""
    count = 0
    i = 0
    while i < len(txt):
        curr= txt[i:i+3]
        l = len(curr)
        if l == 3: 
            for j in range(i+1,len(txt)): 
                if txt[i:i+l] == txt[j:j+l]: 
                    while txt[i:i+l] == txt[j:j+l]:
                        l = l + 1
                    l = l -1
                    curr = txt[i:i+l] 
                    if curr in reps:
                        continue
                    else:
                        diffmap[curr] = (j - i)
                        reps.add(curr)
                    diff = j - i #distance from i to j
                    freq.extend(divisorsOf(diff)) #Flat add divisors 
                    #print ("%s\ti:%s\tj:%s\tdiff:%s\t\tDivisors:%s" % (curr,i,j, diff,divisorsOf(diff))) #Print information about the tuple (can be deleted)
                    info +="%s\t%s\t%s\t%s  \t\t%s\n" % (curr,i,j, diff,divisorsOf(diff))
                    count = count +1
                    j = j + l + 1
            i = i + l -3 +1
        else:
            i = i + 1
    print "Zanotowano %s powtorzen:\nsubstr\tfrom\tto\tdiff\t\tdivisors\n%s" % (count, info)
    return reps, freq, diffmap


def countOcc(mylist): # return list with (decimal_char, occ) 
    d={}
    for el in mylist:
        if d.has_key(el):
            d[el] += 1
        else:
            d[el] = 1
    return sorted(d.items(),key=lambda x: x[1], reverse=True)

def findCh(a):
    avg=99999
    ans=-1
    for i in range(0,26):
        curr=0
        for ch in a:
           # curr += (((a[ chr( (ord(ch)+i)%26 + ord('a') )]-pl[ch])**2)/2)**(1/2)
            curr += math.sqrt(( a[ chr( ((ord(ch)-ord('a') )%26+i)%26 + ord('a') )]-pl[ch] )**2/2.0)
        if curr<avg:
            avg = curr
            ans = i
    return chr(ans+ord('a'))






print("Szyfrogram zawiera " + str(len(szyfrogram)) + " znakow")


## METODA KRASISKIEGO
repRes = repeatsOf(szyfrogram)
diffmap = repRes[2]
repRes = list(repRes[0])

repRes.sort(reverse=True,key = lambda s: len(s))
#print repRes[:7]
repDiv = []
for x in repRes[:7]:
    repDiv.extend(divisorsOf( diffmap[x] ) )

#print "%s" % repDiv
divList = countOcc(repDiv)
#print divList

krasList=[]

for x in divList:
    if x[1]==divList[0][1]:
        krasList.append(x[0])
print "metoda Krasiskiego mowi nam, ze dlugosc klucza wynosi %s" %  (''.join(str(x)+" lub " for x in krasList)[:-4])


## METODA FRIEDMANA
print('')
coincidences = []
for i in range(1,21):
    curr = szyfrogram[i:] + szyfrogram[:i]
    currCoincidences = sum(char1 == char2 for char1,char2 in zip(szyfrogram, curr))
    coincidences.append(currCoincidences)
    print "dla przesuniecia i = %s zanotowano: %s koincydencji " % (i,currCoincidences)    

locMax = [] # index list of local maximas

# for i, x in enumerate(coincidences):
#     if i>0 and i+1<len(coincidences):
#         if x>coincidences[i+1] and x>coincidences[i-1]:
#             locMax.append(i+1)
#     elif i==0 and x>coincidences[i+1]:
#         locMax.append(i+1)
#     elif i+1==len(coincidences) and x>coincidences[i-1]:
#         locMax.append(i+1)

for i, x in enumerate(coincidences):
    left = i-1
    right = i+1
    while left>=0 and coincidences[left]==x:
        left-=1
    while right<len(coincidences) and coincidences[right]==x:
        right+=1
    if right<len(coincidences) and left>=0 and coincidences[left]<x and coincidences[right]<x:
        locMax.append(i+1)
        
print "maksima lokalne obserwowane dla i = %s" % (''.join(str(x)+", " for x in locMax)[:-2])

friedLen = []

divList = []
for i,x in enumerate(locMax):
    xDivides = 0
    for j,y in enumerate(locMax):
        if y%x==0:
            xDivides+=1
    divList.append( (x,xDivides) )

divList.sort(reverse=True,key=lambda tup: tup[1])  # sorts in place

for x in divList:
    if x[1]==divList[0][1]:
        friedLen.append(x[0])

print "metoda Friedmana mowi nam, ze dlugosc klucza wynosi %s" %  (''.join(str(x)+" lub " for x in friedLen)[:-4])

## DESZYFRACJA
print('')
possibleLen = list(set(friedLen) & set(krasList))
if len(possibleLen) == 0:
    possibleLen = list(set(friedLen) | set(krasList))
for keyLen in possibleLen:
    keyProp = ''
    for i in range(0, keyLen):
        chLen = len(szyfrogram[i::keyLen])
        print "pozycja %s:" % (i+1)
        print "ilosc liter: %s" % chLen
        for ch in sorted(alphabet.iterkeys()):
            alphabet[ch] = szyfrogram[i::keyLen].count(ch)
            print "%s\t%s\t%s\t%s" % (ch, alphabet[ch], 1000*alphabet[ch]/chLen, '*'*int(100*alphabet[ch]/chLen) )
        keyProp += findCh(alphabet)
        alphabet = alphabet.fromkeys(alphabet, 0)
        
    print('')
    print "Dla klucza dlugosci %s najlepsza wartosc = %s" % (keyLen, keyProp)
    tekstJawny = ""
    for i,ch in enumerate(szyfrogram):
        tekstJawny+= chr( (ord(ch)-ord(keyProp[i%keyLen]))%26+ord('a') )
    print('')
    print "Wtedy zdeszyfrowany tekst: "
    print tekstJawny
    