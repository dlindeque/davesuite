'use strict';
var Alexa = require("alexa-sdk");
var appId = ''; //'amzn1.echo-sdk-ams.app.your-skill-id';

exports.handler = function(event, context, callback) {
    var alexa = Alexa.handler(event, context);
    alexa.appId = appId;
    alexa.registerHandlers(newSessionHandlers, guessModeHandlers);
    alexa.execute();
};

let allWords = [
    "their",
    "would",
    "about",
    "there",
    "think",
    "which",
    "people",
    "could",
    "other",
    "these",
    "first",
    "because",
    "thing",
    "those",
    "woman",
    "through",
    "child",
    "there",
    "after",
    "should",
    "world",
    "school",
    "still",
    "three",
    "state",
    "never",
    "become",
    "between",
    "really",
    "another",
    "family",
    "leave",
    "while",
    "student",
    "great",
    "group",
    "begin",
    "country",
    "where",
    "problem",
    "every",
    "start",
    "might",
    "about",
    "against",
    "place",
    "again",
    "company",
    "where",
    "system",
    "right",
    "program",
    "during",
    "small",
    "number",
    "always",
    "night",
    "point",
    "believe",
    "today",
    "bring",
    "happen",
    "without",
    "before",
    "large",
    "million",
    "under",
    "water",
    "write",
    "mother",
    "money",
    "story",
    "young",
    "month",
    "right",
    "study",
    "though",
    "issue",
    "black",
    "little",
    "house",
    "after",
    "since",
    "provide",
    "service",
    "around",
    "friend",
    "father",
    "until",
    "power",
    "often",
    "among",
    "stand",
    "however",
    "member",
    "almost",
    "include",
    "later",
    "white",
    "least",
    "learn",
    "change",
    "minute",
    "several",
    "nothing",
    "right",
    "social",
    "whether",
    "watch",
    "follow",
    "around",
    "parent",
    "create",
    "public",
    "already",
    "speak",
    "others",
    "level",
    "allow",
    "office",
    "spend",
    "health",
    "person",
    "history",
    "party",
    "within",
    "result",
    "change",
    "morning",
    "reason",
    "early",
    "before",
    "moment",
    "himself",
    "teacher",
    "force",
    "offer",
    "enough",
    "across",
    "second",
    "maybe",
    "toward",
    "policy",
    "process",
    "music",
    "appear",
    "human",
    "serve",
    "market",
    "expect",
    "sense",
    "build",
    "nation",
    "college",
    "death",
    "course",
    "someone",
    "behind",
    "reach",
    "local",
    "remain",
    "effect",
    "suggest",
    "class",
    "control",
    "raise",
    "perhaps",
    "little",
    "field",
    "former",
    "major",
    "require",
    "along",
    "report",
    "better",
    "effort",
    "decide",
    "strong",
    "heart",
    "leader",
    "light",
    "voice",
    "whole",
    "police",
    "finally",
    "return",
    "price",
    "report",
    "explain",
    "develop",
    "carry",
    "drive",
    "federal",
    "break",
    "better",
    "thank",
    "receive",
    "value",
    "action",
    "model",
    "season",
    "society",
    "because",
    "early",
    "player",
    "agree",
    "record",
    "paper",
    "special",
    "space",
    "ground",
    "support",
    "event",
    "whose",
    "matter",
    "center",
    "couple",
    "project",
    "table",
    "court",
    "produce",
    "teach",
    "figure",
    "street",
    "image",
    "itself",
    "phone",
    "either",
    "cover",
    "quite",
    "picture",
    "clear",
    "piece",
    "recent",
    "product",
    "doctor",
    "patient",
    "worker",
    "movie",
    "certain",
    "north",
    "support",
    "simply",
    "third",
    "catch",
    "source",
    "nearly",
    "choose",
    "cause",
    "point",
    "century",
    "window",
    "listen",
    "culture",
    "billion",
    "chance",
    "brother",
    "energy",
    "period",
    "course",
    "summer",
    "realize",
    "hundred",
    "plant",
    "likely",
    "short",
    "letter",
    "choice",
    "place",
    "single",
    "south",
    "husband",
    "floor",
    "economy",
    "medical",
    "church",
    "close",
    "current",
    "future",
    "wrong",
    "involve",
    "defense",
    "anyone",
    "myself",
    "sport",
    "board",
    "subject",
    "officer",
    "private",
    "fight",
    "throw",
    "quickly",
    "second",
    "order",
    "author",
    "focus",
    "foreign",
    "blood",
    "agency",
    "nature",
    "color",
    "store",
    "reduce",
    "sound",
    "before",
    "enter",
    "share",
    "common",
    "other",
    "natural",
    "concern",
    "series",
    "similar",
    "usually",
    "animal",
    "factor",
    "decade",
    "article",
    "shoot",
    "seven",
    "artist",
    "scene",
    "stock",
    "career",
    "despite",
    "central",
    "eight",
    "beyond",
    "happy",
    "exactly",
    "protect",
    "serious",
    "occur",
    "media",
    "ready",
    "thought",
    "simple",
    "quality",
    "accept",
    "answer",
    "meeting",
    "prepare",
    "disease",
    "success",
    "argue",
    "amount",
    "ability",
    "staff",
    "growth",
    "degree",
    "wonder",
    "attack",
    "herself",
    "region",
    "pretty",
    "trade",
    "general",
    "feeling",
    "message",
    "outside",
    "arrive",
    "benefit",
    "forward",
    "lawyer",
    "present",
    "section",
    "glass",
    "answer",
    "skill",
    "sister",
    "crime",
    "stage",
    "compare",
    "design",
    "station",
    "state",
    "little",
    "clearly",
    "discuss",
    "indeed",
    "force",
    "truth",
    "example",
    "check",
    "public",
    "various",
    "rather",
    "laugh",
    "guess",
    "study",
    "prove",
    "entire",
    "design",
    "enough",
    "forget",
    "since",
    "claim",
    "remove",
    "manager",
    "close",
    "sound",
    "enjoy",
    "network",
    "legal",
    "final",
    "science",
    "green",
    "memory",
    "above",
    "trial",
    "expert",
    "spring",
    "radio",
    "visit",
    "avoid",
    "imagine",
    "tonight",
    "close",
    "finish",
    "theory",
    "impact",
    "respond",
    "charge",
    "popular",
    "reveal",
    "weapon",
    "contain",
    "peace",
    "control",
    "apply",
    "measure",
    "shake",
    "manage",
    "chair",
    "camera",
    "perform",
    "weight",
    "treat",
    "evening",
    "affect",
    "inside",
    "style",
    "adult",
    "worry",
    "range",
    "mention",
    "rather",
    "writer",
    "trouble",
    "middle",
    "dream",
    "instead",
    "improve",
    "stuff",
    "detail",
    "method",
    "hotel",
    "soldier",
    "reflect",
    "heavy",
    "sexual",
    "cause",
    "tough",
    "surface",
    "purpose",
    "exist",
    "pattern",
    "agent",
    "owner",
    "machine",
    "ahead",
    "address",
    "cancer",
    "reality",
    "coach",
    "total",
    "finger",
    "garden",
    "notice",
    "modern",
    "partner",
    "civil",
    "kitchen",
    "budget",
    "capital",
    "mouth",
    "victim",
    "instead",
    "threat",
    "smile",
    "score",
    "account",
    "break",
    "dinner",
    "figure",
    "western",
    "relate",
    "travel",
    "debate",
    "prevent"
];

function getNewWord(usedWords) {
    let wordno = Math.round((Math.random() * allWords.length));
    return allWords[wordno];
}

function startNewGame(attributes) {
    // record the used word
    attributes.usedWords = attributes.usedWords || [];
    if(typeof attributes.word !== "undefined") {
        attributes.usedWords.push(attributes.word);
    }
    
    // guess another word
    attributes.word = getNewWord(attributes.usedWords);
    attributes.usedLetters = [ ];
    attributes.correctLetters = [];
    attributes.guessesLeft = 12;
    for(let i = 0; i < attributes.word.length; i++) {
        attributes.correctLetters[i] = null;
    }
}

function getLetter(letter) {
    if (letter.length === 1) return letter.toUpperCase();
    switch(letter.toUpperCase()) {
        case "ALFA": return "A";
        case "BRAVO": return "B";
        case "CHARLIE": return "C";
        case "DELTA": return "D";
        case "ECHO": return "E";
        case "FOXTROT": return "F";
        case "GOLF": return "G";
        case "HOTEL": return "H";
        case "INDIA": return "I";
        case "JULIETT": return "J";
        case "KILO": return "K";
        case "LIMA": return "L";
        case "MIKE": return "M";
        case "NOVEMBER": return "N";
        case "OSCAR": return "O";
        case "PAPA": return "P";
        case "QUEBEC": return "Q";
        case "ROMEO": return "R";
        case "SIERRA": return "S";
        case "TANGO": return "T";
        case "UNIFORM": return "U";
        case "VICTOR": return "V";
        case "WHISKEY": return "W";
        case "XRAY": return "X";
        case "YANKEE": return "Y";
        case "ZULU": return "Z";
        default: return "Z";
    }
}

function guessLetter(attributes, letter) {
    let rsp = { allreadyUsed: false, foundLetter: false, foundAllLetters: false };

    let l = getLetter(letter);

    for(let ul of attributes.usedLetters) {
        if (ul === l) {
            rsp.alreadyUsed = true;
            return rsp;
        }
    }
    attributes.usedLetters.push(l);

    rsp.foundAllLetters = true;
    for(let i = 0; i < attributes.word.length; i++) {
        if (attributes.correctLetters[i] === null) {
            if (attributes.word[i].toUpperCase() === l) {
                rsp.foundLetter = true;
                attributes.correctLetters[i] = l;
            }
            else {
                rsp.foundAllLetters = false;
            }
        }
    }

    attributes.guessesLeft --;

    return rsp;
}

function getCurrentState(attributes) {
    //You've got 12 guesses left. You've not guessed any correct letters yet and the word contains 8 letters. You've already used, <say-as interpret-as="spell-out">A</say-as>, <say-as interpret-as="spell-out">B</say-as>, and <say-as interpret-as="spell-out">C</say-as>. Get ready for a spoiler..., The word is computer.
    let rsp = "You've got ";
    if (attributes.guessesLeft === 0) {
        rsp = rsp + "no guesses left.";
    }
    else if (attributes.guessesLeft === 1) {
        rsp = rsp + "one guess left.";
    }
    else {
        rsp = rsp + attributes.guessesLeft.toString() + " guesses left.";
    }

    if (attributes.usedLetters.length !== 0) {
        if (attributes.correctLetters.every(letter => letter === null)) {
            rsp = rsp + " You've not guessed any correct letters yet and the word contains " + attributes.word.length.toString() + " letters.";
        }
        else {
            rsp = rsp + " The word is";
            for(let ch of attributes.correctLetters) {
                if (ch === null) {
                    rsp = rsp + ", blank";
                }
                else {
                    rsp = rsp + ", <say-as interpret-as=\"spell-out\">" + ch.toUpperCase() + "</say-as>";
                }
            }
            rsp = rsp + ".";
        }
        
        // You've already used, A, B, and E.
        rsp = rsp + " You've already used";
        if (attributes.usedLetters.length == 1) {
            rsp = rsp + ", <say-as interpret-as=\"spell-out\">" + attributes.usedLetters[0].toUpperCase() + "</say-as>.";
        }
        else {
            for(let i = 0; i < attributes.usedLetters.length - 1; i++) {
                rsp = rsp + ", <say-as interpret-as=\"spell-out\">" + attributes.usedLetters[i].toUpperCase() + "</say-as>";
            }
            rsp = rsp + ", and <say-as interpret-as=\"spell-out\">" + attributes.usedLetters[attributes.usedLetters.length - 1].toUpperCase() +  "</say-as>.";
        }
    }
    else {
        rsp = rsp + " You've not made any guesses yet.";
    }

    return rsp;
}

function getCurrentCardState(attributes) {
    let rsp = "The word:";
    for(let ch of attributes.correctLetters) {
        if (ch === null) {
            rsp = rsp + " _";
        }
        else {
            rsp = rsp + " " + ch.toUpperCase();
        }
    }
}

function spellWord(word) {
    let rsp = "";
    for(let ch of word) {
        rsp = rsp + ", <say-as interpret-as=\"spell-out\">" + ch.toUpperCase() + "</say-as>";
    }
    return rsp;
}

function getCoveredLetters(attributes) {
    var allLetters = {};
    for(let i = 0; i < attributes.correctLetters.length; i++) {
        if (attributes.correctLetters[i] === null) {
            allLetters[attributes.word[i]] = true;
        }
    }
    var coverredLetters = [];
    for(let p in allLetters) {
        coverredLetters.push(p);
    }
    return coverredLetters;
}

var states = {
    GUESSMODE: '_GUESSMODE' // User is trying to guess a letter
};

var newSessionHandlers = {
    NewSession() {
        this.handler.state = states.GUESSMODE;
        startNewGame(this.attributes);
        this.emit(':ask', 
            'Welcome to hangman. I am thinking of a word with ' + this.attributes.word.length.toString() + ' letters. What letter is your first guess?',
            'What letter is your first guess?');
    }
};

var guessModeHandlers = Alexa.CreateStateHandler(states.GUESSMODE, {
    NewSession() {
        this.handler.state = '';
        this.emitWithState('NewSession');
    },
    GuessedLetterIntent() {
        let rsp = guessLetter(this.attributes, this.event.request.intent.slots.letter.value);
        if (rsp.alreadyUsed) {
            this.emit(":askWithCard", "You've already used that letter. What's your next guess?", "What's your next guess for a letter?", "Hangman", getCurrentCardState(this.attributes));
        }
        else if (rsp.foundAllLetters) {
            this.emit(":tell", "Well done! You've found all the letters. The word was " + this.attributes.word + spellWord(this.attributes.word) + ", " + this.attributes.word + ". Thanks for playing.")
        }
        else if (rsp.foundLetter) {
            if (this.attributes.guessesLeft === 0) {
                this.emit(":tell", "You've uncovered a letter, but unfortunately you don't have any guesses left. The word was " + this.attributes.word + spellWord(this.attributes.word) + ", " + this.attributes.word + ". Thanks for playing.");
            }
            else {
                this.emit(":askWithCard", "You've uncovered a letter. " + getCurrentState(this.attributes) + " What's your next guess?", "What's your next guess for a letter?", "Hangman", getCurrentCardState(this.attributes))
            }
        }
        else {
            if (this.attributes.guessesLeft === 0) {
                this.emit(":tell", "Sorry, wrong guess. You don't have any guesses left. The word was " + this.attributes.word + spellWord(this.attributes.word) + ", " + this.attributes.word + ". Thanks for playing.");
            }
            else {
                // see whether it is possible to find the word
                if (getCoveredLetters(this.attributes).length > this.attributes.guessesLeft) {
                    this.emit(":tell", "Sorry, wrong guess. You don't have enough guesses left to guess the whole word. The word was " + this.attributes.word + spellWord(this.attributes.word) + ", " + this.attributes.word + ". Thanks for playing.");
                }
                else {
                    this.emit(":askWithCard", "You've not found a letter. What's your next guess?", "What's your next guess for a letter?", "Hangman", getCurrentCardState(this.attributes))
                }
            }
        }
    },
    RestartIntent() {
        startNewGame(this.attributes);
        this.emit(":ask", "OK. I am thinking of a new word with " + this.attributes.word.length.toString() + ' letters. What letter is your first guess?',
            'What letter is your first guess?');
    },
    CurrentStateIntent() {
        this.emit(":askWithCard", getCurrentState(this.attributes) + " What's your next guess?", "What's your next guess for a letter?", "Hangman", getCurrentCardState(this.attributes));
    },
    'AMAZON.HelpIntent': function() {
        this.emit(":askWithCard", "You can say the letter you've guessed, even using the NATO phonetic alphabet, say \"begin new word\", to start a new game, say \"what is the word\", to get the current state of your game, and say, \"stop\", to stop. " + getCurrentState(this.attributes) + " What's your next guess?", "What's your next guess for a letter?", "Hangman", getCurrentCardState(this.attributes));
    },
    'AMAZON.StartOverIntent': function() {
        startNewGame(this.attributes);
        this.emit(":ask", "OK. I am thinking of a new word with " + this.attributes.word.length.toString() + ' letters. What letter is your first guess?',
            'What letter is your first guess?');
    },
    'AMAZON.StopIntent': function() {
        this.emit(":tell", "OK. Thanks for playing hangman");
    },
    'AMAZON.CancelIntent': function() {
        this.emit(":tell", "OK. Thanks for playing hangman");
    },
    Unhandled() {
        this.emit(":ask", "Sorry, I didn't get that. What's your next guess?", "What's your next guess for a letter?");
    }
});