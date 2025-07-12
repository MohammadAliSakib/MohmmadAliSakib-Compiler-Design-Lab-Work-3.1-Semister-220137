// session 5
#include <iostream>
#include <string>
#include <cctype>

using namespace std;

string input;
int i = 0;  // Pointer to traverse input string

// Forward declarations of the parsing functions
void parseStat();
void parseAsgnStat();
void parseExpn();
void parseSmplExpn();
void parseExtn();
void parseRelop();
void parseDscnStat();
void parseLoopStat();
void parseExtn1();

// Function to parse the statement (<stat>)
void parseStat() {
    if (input[i] == 'i') {  // Start of an if statement
        parseDscnStat();
    } else if (input[i] == 'w') {  // Start of a while statement
        parseLoopStat();
    } else {  // Start of an assignment
        parseAsgnStat();
    }
}

// Function to parse an assignment (<asgn_stat>)
void parseAsgnStat() {
    if (input[i] == 'i' || input[i] == 'a') {  // Assuming we have a single character identifier
        i++;  // Skip the 'id'
        if (input[i++] == '=') {  // Expect '=' for assignment
            parseExpn();  // Parse the expression on the right-hand side
        } else {
            cout << "Syntax error: Expected '='." << endl;
        }
    }
}

// Function to parse the expression (<expn>)
void parseExpn() {
    parseSmplExpn();  // Parse the simple expression part
    parseExtn();      // Parse any extensions (like relational operators)
}

// Function to parse simple expression (<smpl_expn>)
void parseSmplExpn() {
    if (isdigit(input[i])) {
        cout << "Parsed number: " << input[i++] << endl;
    } else {
        cout << "Syntax error: Expected number in simple expression." << endl;
    }
}

// Function to parse extensions (<extn>) like relational operators
void parseExtn() {
    if (input[i] == '=' || input[i] == '!' || input[i] == '<' || input[i] == '>') {
        parseRelop();  // Parse the relational operator
        parseSmplExpn();  // Parse the second simple expression
    }
}

// Function to parse relational operators (<relop>)
void parseRelop() {
    if (input[i] == '=') {
        i++;  // Skip the '='
    } else if (input[i] == '!') {
        i++;  // Skip the '!'
        if (input[i++] != '=') {
            cout << "Syntax error: Expected '='" << endl;
        }
    } else {
        i++;  // Skip the relational operator
    }
}

// Function to parse a decision statement (<dscn_stat>) like an if statement
void parseDscnStat() {
    if (input[i++] == 'i' && input[i++] == 'f') {
        if (input[i++] == '(') {
            parseExpn();  // Parse the expression inside the parentheses
            if (input[i++] == ')') {
                parseStat();  // Parse the statement after 'if'
                parseExtn1();  // Parse any "else" part
            } else {
                cout << "Syntax error: Expected ')'" << endl;
            }
        }
    }
}

// Function to parse the else extension (<extn1>) of an if statement
void parseExtn1() {
    if (input[i] == 'e') {
        i++;  // Skip the 'e'
        if (input[i++] == 'l' && input[i++] == 's' && input[i++] == 'e') {
            parseStat();  // Parse the statement after "else"
        }
    }
}

// Function to parse a loop statement (<loop_stat>) like while or for
void parseLoopStat() {
    if (input[i++] == 'w') {
        if (input[i++] == 'h' && input[i++] == 'i' && input[i++] == 'l' && input[i++] == 'e') {
            if (input[i++] == '(') {
                parseExpn();  // Parse the condition in parentheses
                if (input[i++] == ')') {
                    parseStat();  // Parse the statement in the loop body
                }
            }
        }
    } else if (input[i++] == 'f') {
        if (input[i++] == 'o' && input[i++] == 'r') {
            if (input[i++] == '(') {
                parseAsgnStat();  // Parse the assignment statement
                if (input[i++] == ';') {
                    parseExpn();  // Parse the condition in the loop
                    if (input[i++] == ';') {
                        parseAsgnStat();  // Parse the assignment after the condition
                        if (input[i++] == ')') {
                            parseStat();  // Parse the statement inside the loop
                        }
                    }
                }
            }
        }
    }
}

int main() {
    cout << "Enter a program string: ";
    cin >> input;  // Example input: "a=3; if (a==5) b=6; else c=7;"

    parseStat();  // Start parsing from the statement rule
    return 0;
}
