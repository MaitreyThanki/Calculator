import java.util.*;
// import java.lang.*;

class calculator{
   
    // Getting precedent
    static int perd(char op) {
        if (op == '+' || op == '-') return 1;
        if (op == '*' || op == '/') return 2;
        if (op == '^') return 3;
        return 0;
    }

    //Infix to Postfix
    static String postfix(String exp) {
        StringBuilder postexp = new StringBuilder();
        Stack<Character> stack = new Stack<>();

        int i = 0; //index

        //Loop till lenght
        while (i < exp.length()) {

            //White spaces remove
            if (Character.isWhitespace(exp.charAt(i))) {
                i++;
                continue;
            }

            //Digits
            if (Character.isDigit(exp.charAt(i))) {
                while (i < exp.length() && Character.isDigit(exp.charAt(i))) {
                    postexp.append(exp.charAt(i));
                    i++;
                } 
                postexp.append(' ');
            }

            // ( 
            else if (exp.charAt(i) == '(') {
                stack.push(exp.charAt(i));
                i++;
            }

            // Popping till (
            else if (exp.charAt(i) == ')') {
                while(!stack.isEmpty() && stack.peek() != '(') {
                    postexp.append(stack.pop()).append(' ');
                }
                stack.pop();
                i++;
            }

            //oprands
            else {
                while (!stack.isEmpty() && perd(stack.peek()) >= perd(exp.charAt(i))){
                    postexp.append(stack.pop()).append(' ');
                }
                stack.push(exp.charAt(i));
                i++;
            }
        }

        //Emtying stack
        while (!stack.isEmpty()) {
           postexp.append(stack.pop()).append(' ');
        }

        return postexp.toString();
    }

    //Postfix Evaluation
    static int evaluation(String post) {
        
        Stack<Integer> stack = new Stack<>();
        int i = 0;

        while (i < post.length()) {

            if (post.charAt(i) == ' ') {
                i++;
                continue;
            }

            // number
            if (Character.isDigit(post.charAt(i))) {
                int num = 0;
                while (i < post.length() && Character.isDigit(post.charAt(i))) {
                    num = num * 10 + (post.charAt(i) - '0');
                    i++;
                }
                stack.push(num);
            }

            // operator
            else {
                int b = stack.pop();
                int a = stack.pop();

                switch (post.charAt(i)) {
                    case '+': stack.push(a + b); break;
                    case '-': stack.push(a - b); break;
                    case '*': stack.push(a * b); break;
                    case '/': stack.push(a / b); break;
                    case '^': stack.push((int)Math.pow(a, b)); break;
                }
                i++;
            }
        }

        return stack.peek();
    } 

    public static void main(String args[]) {
        Scanner sc = new Scanner(System.in);

        System.out.print("Enter Expresion: ");
        String exp = sc.nextLine();
        String postexp = postfix(exp);

        int result = evaluation(postexp);

        System.out.println("Entered Experation: " + exp);
        
        System.out.println("Postfix Expresion: " + postfix(exp));

        System.out.println("Answer = " + result);
        
        sc.close();
    }
}