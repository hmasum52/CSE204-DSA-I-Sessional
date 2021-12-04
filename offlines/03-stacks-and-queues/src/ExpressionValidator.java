public class ExpressionValidator {
    private Stack<Double> operand;
    private Stack<Operator> operator;
    private Double ans = null;

    /**
     * for mapping character operator
     */
    enum Operator {
        START_PARENTHESIS, CLOSE_PARENTHESIS, PLUS, MINUS, UNARY_MINUS, MULTIPLICATION, DIVISION;

        /**
         * @return true if the operator has higher or same precedence as @param o
         */
        public boolean isPrecede(Operator o) {
            //we know parenthesis has the higher precedence
            //so true false as will have lower precedence 
            //we don't consider ) as we will not insert it to the stack 
            if (this == START_PARENTHESIS)
                return false;
            
            //another case when the operator has lower precedence
            //is when the operator is + or - but o is * or /
            if ((this == PLUS || this == MINUS) && (o == MULTIPLICATION || o == DIVISION))
                return false;

            //in all other cases the operator
            //has equal or higher precedence
            return true;
        }


        /**
         * map operator character with 
         */
        public static Operator map(char ch) {
            switch (ch) {
            case '+':
                return PLUS;
            case '-':
                return MINUS;
            case '*':
                return MULTIPLICATION;
            case '/':
                return DIVISION;
            }
            return null;
        }
    }

    public ExpressionValidator() {
        operand = new Stack<>();
        operator = new Stack<>();
    }

    /**
     * @param exp is the expression to be validated 
     * @return true is the expression is valid.
     */
    public boolean validate(String exp) {
        try {
            char[] charArr = exp.toCharArray();
            String num = ""; //to store nums greater than 2 digits
            int i = 0;

            // ITERATE THE EXPRESSION ==============
            for (Character ch : charArr) {

                if (ch == ' ') {
                    // "Whitespace is not allowed";
                    return false;
                }

                // PARSE NUMBER ====================
                //if the character is not a part of number
                //than parse already stored number in the number
                //and add it to operand stack
                if (!num.equals("") && !((ch >= '0' && ch <= '9') || ch == '.')) {
                    if(!parseAndPushNumberToStack(num))
                        return false;
                    num = "";
                }

                // PUSH THE OPERATORS =========================
                if (ch == '(')
                    operator.push(Operator.START_PARENTHESIS);

                // UNARY MINUS OPERATOR =======================
                //check is the operator is a UNARY MINUS operator
                //only '(-1)' this form of unary minus is valid
                else if (ch == '-' && (i > 0 && charArr[i - 1] == '(')) {
                    operator.push(Operator.UNARY_MINUS);
                }

                // BINARY OPERATORS ===========================
                //character is the operator is a binary operator
                else if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
                    if (!pushBinaryOperatorToStack(ch)) {
                        return false;
                    }
                }

                // END PARENTHESIS ===========================
                else if (ch == ')') {
                    if (!popStartAndCompute()) {
                        return false;
                    }
                }

                // NUMBER================
                // the character is a part of a number
                else {
                    num += ch;
                }

                // DUBUG ====================
                /*  System.out.print(i + " kop: " + ch + " ");
                if (!operand.isEmpty())
                 System.out.print("operand: " + operand.top() + " ");
                if (!operator.isEmpty())
                 System.out.print("operator: " + operator.top());
                System.out.println(); */

                //to access next character
                i++;
            }

            // NUMBER =========================
            // check if last char was a part of a number
            if (!num.equals("")) {
                if (!parseAndPushNumberToStack(num))
                    return false;
                num = "";
            }

            // System.out.println("Doing final operations");

            // DO FINAL OPERATIONS ==============
            // at this point if the expression is valid
            // all parenthesis operations are done
            // so do the final operations
            while (!operator.isEmpty()) {
                double o2 = operand.pop();
                Operator op = operator.pop();
                double o1 = operand.pop();

                //send o2 1st as the values are pushed in a stack
                Double value = compute(o2, op, o1);
                if (value == null) {
                    // error doing binary operation.
                    return false;
                }
                operand.push(value);
            }

            // ANSWER ======================
            // at this point top element of operand stack 
            // is the comupted value of the expression
            // if it is a valid one
            ans = operand.top();

            // VALID EXPRESION ==============
            // return true as the expresion is valid
            return true;

        } catch (Exception e) {
            // e.printStackTrace();
            return false;
        }
    }

    private boolean parseAndPushNumberToStack(String num) {
        try {
            // if it is a part of a number than parse it
            operand.push(Double.parseDouble(num));
            return true;
        } catch (Exception e) {
            // error parsing number
            return false;
        }
    }

    private boolean pushBinaryOperatorToStack(char ch) {
        // map the binary operator
        Operator op = Operator.map(ch);

        // then checks the precedene of the operator with previously pushed
        // binary operators and do the operations first
        while (!operator.isEmpty() && operator.top().isPrecede(op)) {
            // System.out.println("Note: " + operator.top() + " has higher precedence than "
            // + ch);
            Double value = compute(operand.pop(), operator.pop(), operand.pop());
            if (value == null) {
                // error doing binary operation.
                return false;
            }
            operand.push(value);
        }
        operator.push(op);
        return true;
    }

    private boolean popStartAndCompute() {
        // if top operator is a UNARY MINUS then negate the top operand
        if (operator.top() == Operator.UNARY_MINUS) {
            // System.out.println("doUnaryOperation: operation > MINUS " + operand.top());
            operand.push(-operand.pop()); // negate the top
            operator.pop(); // pop unary minus
            operator.pop(); // pop (
        } else {
            // if it is not UNIARY MINUS
            // then look for '('
            // and do binary operations
            // until the '(' is found or stacks are not empty
            while (!operator.isEmpty() && !operand.isEmpty()) {
                if (operator.top() == Operator.START_PARENTHESIS) {
                    operator.pop();
                    break;
                }
                Double value = compute(operand.pop(), operator.pop(), operand.pop());
                if (value == null) {
                    return false;
                }
                operand.push(value);
            }
        }
        return true;
    }

    /**
     * 
     * @param o2 2nd operand
     * @param operator
     * @param o1 1st operand
     * @return  a double value of operation o1 (operator) o1 .... 5*6 for example
     * if operator doesn't match then return a null valu
     */
    private Double compute(double o2, Operator operator, double o1) {
        //System.out.println("doBinaryOperation: operation >   " + o1 + " " + operator + " " + o2);
        switch (operator) {
        case PLUS:
            return o1 + o2;
        case MINUS:
            return o1 - o2;
        case MULTIPLICATION:
            return o1 * o2;
        case DIVISION:
            try {
                return o1 / o2;
            } catch (Exception e) {
                e.printStackTrace();
                return null;
            }
        default:
            break;

        }
       // System.out.println("binarayOperation: " + operator + " operator deesn't match");
        return null;
    }

    /**
     * 
     * @return a double value for valid expression
     * and return null for an invalid expression
     */
    public double getAnswer() {
        return ans;
    }

    /**
     * for debugging
     * @return a test case
     */
    public String getTestCase() {
        String exp;
        // exp = "(9*3-(7*8+((-4)/2)))"; // -27
        // exp = "(9*3-(7*8+((-(-4))/2)))"; // -31
        // exp = "12*(-1)"; // -12
        // exp = "12*123/((-5)+2)"; //-4921
        // exp = "((80-(19)))"; //61
        // exp = "(1-2)+(((-4)))"; //-5
        // exp = "1+1"; //2
        // exp = "2/2+3*4.75-6"; //9.25
        // exp = "2/2+3*4.75--6"; //invalid
        // exp = "12*(-123)"; //-1476
        // exp = "2/(2+3)*4.33-(-6.792)"; // 8.524000000000001
        // exp = "((2.33/(2.9+3.5)*4)-(-6.34))"; // 7.79625
        // exp = "123.45*(678.90/((-2.5)+11.5)-(80-19)*33.25)/20+11"; // -12042.760875
        // exp =
        // "(123.45*(678.90/((-2.5)+11.5)-(((80-(19)))*33.25))/20)-(123.45*(678.90/(-2.5+11.5)-(((80-(19)))*33.25))/20)+(13-2)/(-11)";
        // //invalid
        // exp =
        // "(123.45*(678.90/((-2.5)+11.5)-(((80-(19)))*33.25))/20)-(123.45*(678.90/((-2.5)+11.5)-(((80-(19)))*33.25))/20)+(13-2)/(-11)";
        // //
        // exp = "1-1-1";
        // exp = "6/2*3"; //9
        // exp = "2/2-3*4-6"; //-17
        // exp = "12*(-123) = -1476";
        // exp = "123.45*(678.90/(-2.5+11.5)-(80-19)*33.25)/0+11";
        // exp = "52";
        // exp = "-52";//ivalid
        // exp = "(-52)";
        // exp = "(((1-5)+( 3.93* 2.34)* 10)+(10+10+19-8*7/6+10))"; //
        // 127.62866666666665
        // exp = "(9*3-(7*8+((-4/2)))"; //invalid
        exp = "(-1)-(-3)"; // 2
        exp = "((-1)-(-3))";
        return exp;
    }
}
