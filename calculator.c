#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
//global values
char stack[50];
int top = -1;

//get precedent
char pred(char exp) {
    if(exp == '+' || exp == '-') return 1;
    if(exp == '*' || exp == '/') return 2;
    if(exp == '^') return 3;
    return 0;
}

//push
void push(char val){
    stack[++top] = val;
}
//pop
char pop(){
    return stack[top--];
}
//get top value
char peek(){
    if (top == -1) return 0;
    return stack[top];
}

//infix to postfix
void postfix(char exp[], char postexp[]) {
    int j = 0;//pointer to exp
    int k = 0;//pointer to postexp
    while(exp[j] != '\0') {

        // keeping digits together
        if(isdigit(exp[j])) {

            while(isdigit(exp[j])){
                postexp[k++] = exp[j++];
            }
            postexp[k++] = ' '; //delimiter
        }
        
        //pushing (
        else if(exp[j] == '(') push(exp[j++]);

        //pop till (
        else if(exp[j] == ')'){
            while (peek() != '('){
                postexp[k++] = pop();
                postexp[k++] = ' '; 
            }
            pop(); //popping 
            j++;
        }
        
        //noise
        else if (exp[j] == ' ' || exp[j] == '\n' || exp[j] == '\t') {
            j++;
        }

        //operators
        else if (exp[j] == '+' || exp[j] == '-' || exp[j] == '*' || exp[j] == '/' || exp[j] == '^') {
            while (top != -1 && pred(peek()) >= pred(exp[j])) {
                postexp[k++] = pop();
                postexp[k++] = ' ';
            }
            push(exp[j++]);
        } 
    }

    //if values remaining 
    while(top != -1) {
        postexp[k++] = pop();
        postexp[k++] = ' ';
    }
    postexp[k] = '\0';


}
//evaluation of postfix
int evaluate(char postexp[]) {
    
    int i = 0;
    int itop = -1; //internal top
    int numstack[50];
    
    while(postexp[i] != '\0'){
        
        //removing whitespace
        if(postexp[i] == ' ') {
            i++;
            continue;
        }

        //storing digits in stack
        if(isdigit(postexp[i])) {
            int num = 0;
            while(isdigit(postexp[i])) {
                num = num * 10 + (postexp[i] - '0');
                i++;
            }
            numstack[++itop] = num;
        }

        //operations
        else {
            int val1 = numstack[itop--];
            int val2 = numstack[itop--];
        
             switch (postexp[i]) {
                case '+': numstack[++itop] = val1 + val2; break;
                case '-': numstack[++itop] = val1 - val2; break;
                case '*': numstack[++itop] = val1 * val2; break;
                case '/': numstack[++itop] = val1 / val2; break;
               // case '^': numstack[++itop] = pow(val1, val2); break;
            }
            i++;
        }
    }
    return numstack[itop];
}


int main() {
    char exp[50];
    char postexp[100];
    
    //Entering values
    printf("Enter string: ");
    fgets(exp, sizeof(exp), stdin);
    
    //cleaning up end
    exp[strcspn(exp, "\n")] = '\0';
    printf("Given expression: %s\n", exp);
    
    //validating postfix
    postfix(exp,postexp);
    printf("Postfix expression: %s\n", postexp);
    
    //final output
    int ans = evaluate(postexp);
    printf("Answer: %d\n", ans);
    
    return 0;
}