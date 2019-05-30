// Assumptions for raw-text/key/crypted-text
// 1. Latin alphabet
// 2. Only lower-case characters

const cryptogram = document.getElementById('cryptogram');
const cryptoKey = document.getElementById('cryptokey');
const mykey = document.getElementById('mykey');
const rawText = document.getElementById('rawtext');
const fbutton = document.getElementById('friedman-test');
const kbutton = document.getElementById('kasiski-test');
const sbutton = document.getElementById('stat-test');
const mylen = document.getElementById('mylen');
const mylog = document.getElementById('mylog');

mylog.hidden = true;

const alphabet = "abcdefghijklmnopqrstuvwxyz".split('');
let s = cryptogram.textContent.replace(/\s+/g, ""); // delete whitespaces
let len = s.length; // get cryptogram length
let keyLen = 5;
const freq = {
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
}; // Corresponds to avg letter frequency in a Polish language text
console.log('szyfrogram zawiera ' + len + ' znakow');

// convert from ascii number to char
function znak(x){
    return String.fromCharCode(x);
}
// convert from char to ascii number
function kod(x){
    return x.charCodeAt(0);
}

// reverse-transpose a by b
function rtrans (a, b){
    return znak(kod('a') + (26 + kod(a) - kod(b) )%26);
}

// transpose a by b
function trans (a, b){
    return znak(kod('a') + ( kod(a) - kod('a') + ( kod(b) - kod('a') ) ) %26 );
}

function caesar(t, key){
    let s = "";
    for(let i=0; i<t.length; i++){
        s+=trans(t[i],key);
    }
    return s;
}

// only allow letters from 'a' to 'z' for the key input
mykey.addEventListener('input', function(e){
    let t="";
    mykey.value = mykey.value.replace(/[^a-z]+/g, '')
    let k=mykey.value;
    if(k.length===0)k='a';
    for(let i=0;i<len;i++){
        t+= rtrans( s[i], k[ i%k.length ]);
        if(i%5==4)t+=' ';
    }
    
    rawText.textContent = t;
});
mykey.dispatchEvent(new Event("input"));


mylen.addEventListener('input', function(e){
    mylen.value = mylen.value.replace(/[^0-9]+/g, '');
    if(mylen.value>len){
        mylen.value = len;
    }
    keyLen = Number(mylen.value);
});

kbutton.addEventListener('click', function(e){
    mylen.value = kasiski(s);
    keyLen = Number(mylen.value);
});

fbutton.addEventListener('click', function(e){
    mylen.value = friedman(s);
    keyLen = Number(mylen.value);
   //mykey.value = charfreq(s,alphabet,freq,keyLen);
    //mykey.dispatchEvent(new Event("input"));
});

sbutton.addEventListener('click', function(e){
    mykey.value = charfreq(s,alphabet,freq,keyLen);
    mykey.dispatchEvent(new Event("input"));
});

function charfreq(s,alphabet,freq,keyLen){
    let chunks = [];
    let keyword = "";
    for(i=0; i<keyLen; i++){
        let counts = {}; // init alphabet map with zeroes
        alphabet.forEach( function(x){ counts[x]=0; } );
        
        let chunkLen =  parseInt( (len)/keyLen + ( i<(len%keyLen) ) );
        // count char occurences
        for(let j=i; j<len; j+=keyLen){
            counts[ s[j] ]++;
        }

        let chunkFreq = {};
        alphabet.forEach( function(x){ chunkFreq[x]=+(counts[x]*1000/chunkLen).toFixed(0); ; } );
        chunks.push( {'pos':i+1, 'counts': counts, 'len': chunkLen, 'freq': chunkFreq} );
    }

    console.log('dla |K| = '+keyLen+'\n\n');
    for(let i = 0; i < keyLen; i++){
        console.log(`pozycja ${i+1}:`);
        //mylog.value+=`pozycja ${i+1}:`+'\n';
        alphabet.forEach( function(ch){
            let stars = '*'.repeat( parseInt(chunks[i].freq[ch]/10) );
            let s = `${ch}\t${chunks[i].counts[ch] }\t${chunks[i].freq[ch]}\t${stars}`
            console.log(s);
            //mylog.value+=s+'\n';
        })
        console.log('\n');
    }
    //console.log(chunks);
    // berek 
    console.log(`Root Mean Square of a character per position`);
    let rms = [];
    for(let p=0; p<keyLen; p++){
        rms[p] = [];
        for(let i=0;i<26;i++){
            let curr = alphabet[i];
            let sum = 0;
            alphabet.forEach( function(ch){
                sum += ( freq[ch] - chunks[p].freq[ trans(ch, curr) ] )*(  freq[ch] - chunks[p].freq[ trans(ch, curr) ] )/26;
                //sum += ( freq[ trans(ch, curr) ] - chunks[p].freq[ ch ] )*( freq[ trans(ch, curr) ] - chunks[p].freq[ ch ] )/26;
            });
            rms[p].push(sum);
        }
        //console.log(rms[p])
        console.log(`position ${p+1}:`);
        rms[p].forEach( function(x,ind){
            console.log(`${alphabet[ind]}:\t\t${x}`)
        })
        //let ptr = (25 - rms[p].indexOf(Math.min(...rms[p]) ) ) % 26;
        let ptr = ( rms[p].indexOf(Math.min(...rms[p]) ) ) % 26;
        //console.log(ptr);
        //console.log(rms[p]);
        
        //console.log(alphabet[ptr]); 
        keyword += alphabet[ptr];
    }
    return keyword;
}


function friedman(s, checkSize){
    let bestLen = 0;
    let bestIc = 99;
    let plIc = 0.052967681;
    let enIc = 0.0667;
    let shiftMap = [];

    checkSize = (typeof checkSize !== 'undefined') ? Math.min(checkSize,s.length) : Math.min(16, s.length);
    for(let sh = 1; sh < checkSize; sh++){
        let avgIc = 0;
        for(let startCh=0; startCh<sh; startCh++){
            line = "";
            for(let i=startCh; i<s.length;i+=sh){
                line += s[i];
            }
            avgIc += Number(indexOfCoincidence(line));
        }
        avgIc = avgIc/sh;
        if( Math.abs(avgIc - plIc) < Math.abs(bestIc - plIc) ){
            bestIc = avgIc;
            bestLen = sh;
        }
        
        let deltaIc = Math.abs(avgIc - plIc);
        shiftMap.push( {sh, deltaIc} );
        //console.log(`for shift ${sh} |delta_Ic|% = ${100*Math.abs(avgIc - plIc)/plIc}%`);
    }
    shiftMap.sort( function(a,b){
        return a.deltaIc - b.deltaIc;
    });
    console.log("Friedman test result:")
    shiftMap.forEach( function(x){
        console.log(`for shift ${x.sh} |delta_Ic|% = ${100*Math.abs(x.deltaIc)/plIc}%`)
    });

    return bestLen;
}


function indexOfCoincidence(s){
    let N = s.length;
    let Fi = {};
    alphabet.forEach( function(x){ Fi[x]=0; } );
    for(let i=0;i<N;i++){
        Fi[ s[i] ]++;
    }
    let IC = 0;
    alphabet.forEach( function(x){ if(Fi[x]!=0) IC+=Fi[x]*(Fi[x]-1) } );
    IC/=(N*(N-1));
    return IC;
}


// Kasiski examination
function kasiski(s, checkSize){
    let i = 3;
    var re = new RegExp("([a-z]{"+i+",})(?=.*\\1)","gi");
    var patts = s.match(re);    
    patts.sort( (a,b)=>{return b.length - a.length;} );

    let lenFactors = {};

    checkSize = (typeof checkSize !== 'undefined') ?  Math.min(checkSize,patts.length) : patts.length;

    let repAnalysis = `coincidences (${checkSize}) are: \n`;
    for(let i=0;i<checkSize;i++){
        let first = s.indexOf( patts[i] );
        let second = s.indexOf( patts[i], first+1 );
        getFactors(second-first).forEach( (x)=>{
            if( lenFactors[x] === undefined )
                lenFactors[x] = 1;
            else
                lenFactors[x]++;
        } );
        
        let newLine = `\t${first}\t\t${second}\t\t${second-first}\t\t${patts[i]}\n`;
        repAnalysis += newLine;
    }

    let bestLen = 0;
    let maxOccurence = 0;
    for(const curr in lenFactors){
        if( lenFactors[curr] >= maxOccurence ){
            maxOccurence = lenFactors[curr];
            bestLen = curr;
        }
    }
    //console.log(patts);
    //console.log(lenFactors);
    console.log(repAnalysis);
    return Number(bestLen);
}

// except 1
function getFactors(num) {
    const isEven = num % 2 === 0;
    let inc = isEven ? 1 : 2;
    let factors = [num];
  
    for (let curFactor = isEven ? 2 : 3; Math.pow(curFactor, 2) <= num; curFactor += inc) {
      if (num % curFactor !== 0) continue;
      factors.push(curFactor);
      let compliment = num / curFactor;
      if (compliment !== curFactor) factors.push(compliment);
    }
  
    return factors;
  }
// Friedman test

