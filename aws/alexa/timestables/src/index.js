'use strict';
var Alexa = require("alexa-sdk");
var appId = ''; //'amzn1.echo-sdk-ams.app.your-skill-id';

exports.handler = function(event, context, callback) {
    var alexa = Alexa.handler(event, context);
    alexa.appId = appId;
    alexa.registerHandlers(newSessionHandlers, answerModeHandlers);
    alexa.execute();
};

const constants = {
    operators: {
        add: 1,
        subtract: 2,
        multiply: 3,
        divide: 4
    }
}

function getNumber() {
    return Math.round(Math.random() * 12);
}

function getNewChallenge() {
    let n1 = getNumber();
    let n2 = getNumber();

    switch(Math.round(Math.random() * 3)) {
        case 0: // add
            return {
                first: n1,
                operator: constants.operators.add,
                second: n2,
                answer: n1 + n2
            }
        case 1: // subtract
            if (n1 > n2) {
                return {
                    first: n1,
                    operator: constants.operators.subtract,
                    second: n2,
                    answer: n1 - n2
                }
            }
            else {
                return {
                    first: n2,
                    operator: constants.operators.subtract,
                    second: n1,
                    answer: n2 - n1
                }
            }
        case 2: // multiply
            return {
                first: n1,
                operator: constants.operators.multiply,
                second: n2,
                answer: n1 * n2
            }
        case 3: // divide
            if (n1 === 0) {
                return getNewChallenge();
            }
            else {
                let ans = n1 * n2;
                return {
                    first: ans,
                    operator: constants.operators.divide,
                    second: n1,
                    answer: n2
                }
            }
    }

    return {
        first: 3,
        operator: constants.operators.add,
        second: 7,
        answer: 10
    }
}

function startNewChallenge(attributes) {
    attributes.challenge = getNewChallenge();
}

function getChallengeText(challenge) {
    switch(challenge.operator) {
        case constants.operators.add:
            return "What is " + challenge.first.toString() + " plus " + challenge.second.toString() + "?";
        case constants.operators.subtract:
            return "What is " + challenge.first.toString() + " take away " + challenge.second.toString() + "?";
        case constants.operators.multiply:
            return "What is " + challenge.first.toString() + " times " + challenge.second.toString() + "?";
        case constants.operators.divide:
            return "What is " + challenge.first.toString() + " divided by " + challenge.second.toString() + "?";
        default: return "Unknown operator!";
    }
}

var states = {
    ANSWERMODE: '_ANSWERMODE' // User is trying to guess a letter
};

var newSessionHandlers = {
    NewSession() {
        this.handler.state = states.ANSWERMODE;
        startNewChallenge(this.attributes);
        this.emit(':ask', 
            'Welcome to times tables. ' + getChallengeText(this.attributes.challenge),
            getChallengeText(this.attributes.challenge));
    }
};

var answerModeHandlers = Alexa.CreateStateHandler(states.ANSWERMODE, {
    NewSession() {
        this.handler.state = '';
        this.emitWithState('NewSession');
    },
    AnswerIntent() {
        let answer = Number(this.event.request.intent.slots.answer.value);
        if (answer === this.attributes.challenge.answer) {
            // Found it !
            startNewChallenge(this.attributes);
            this.emit(":ask", "Correct! " + getChallengeText(this.attributes.challenge), getChallengeText(this.attributes.challenge));
        }
        else {
            // Wrong :(
            this.emit(":ask", "Sorry, " + answer.toString() + " is incorrect. " + getChallengeText(this.attributes.challenge), getChallengeText(this.attributes.challenge));
        }
    },
    RestartIntent() {
        startNewChallenge(this.attributes);
        this.emit(":ask", getChallengeText(this.attributes.challenge), getChallengeText(this.attributes.challenge));
    },
    CurrentStateIntent() {
        this.emit(":ask", getChallengeText(this.attributes.challenge), getChallengeText(this.attributes.challenge));
    },
    'AMAZON.HelpIntent': function() {
        this.emit(":ask", "You can say, help, the number you think is the answer, stop, or, what's going on. " + getChallengeText(this.attributes.challenge), getChallengeText(this.attributes.challenge));
    },
    'AMAZON.StartOverIntent': function() {
        startNewChallenge(this.attributes);
        this.emit(":ask", "OK. " + getChallengeText(this.attributes.challenge), getChallengeText(this.attributes.challenge));
    },
    'AMAZON.StopIntent': function() {
        this.emit(":tell", "OK. Thanks for playing times tables");
    },
    'AMAZON.CancelIntent': function() {
        this.emit(":tell", "OK. Thanks for playing times tables");
    },
    Unhandled() {
        this.emit(":ask", "Sorry, I didn't get that. " + getChallengeText(this.attributes.challenge), getChallengeText(this.attributes.challenge));
    }
});