import java.util.Stack;

import java.io.*;
import java.util.Scanner;

public class StackEmulator {
    final int MAX_CODE = 65536; // size of code memory
    final int MAX_DATA = 65536; // size of data memory

    final int HALT = 0; // a few opcodes defined
    final int PUSH = 1;
    final int RVALUE = 2;
    final int LVALUE = 3;
    final int POP = 4;
    final int STO = 5;
    final int COPY = 6;
    final int ADD = 7;
    final int SUB = 8;
    final int MPY = 9;
    final int DIV = 10;
    final int MOD = 11;
    final int NEG = 12;
    final int NOT = 13;
    final int OR = 14;
    final int AND = 15;
    final int EQ = 16;
    final int NE = 17;
    final int GT = 18;
    final int GE = 19;
    final int LT = 20;
    final int LE = 21;
    final int LABEL = 22;
    final int GOTO = 23;
    final int GOFALSE = 24;
    final int GOTRUE = 25;
    final int PRINT = 26;
    final int READ = 27;
    final int GOSUB = 28;
    final int RET = 29;
    final int ORB = 30;
    final int ANDB = 31;
    final int XORB = 32;
    final int SHL = 33;
    final int SHR = 34;
    final int SAR = 35;

    int[] codeStream;
    int[] data;
    int pc;
    int ir;
    boolean run;
    Stack<Integer> stack;
    Stack<Integer> callStack;
    int rvalue;
    int lvalue;

    public StackEmulator() {

        codeStream = new int[MAX_CODE]; // constructor initializes the stack machine;
        data = new int[MAX_DATA];
        pc = 0;
        run = true;
        stack = new Stack<Integer>();
        callStack = new Stack<Integer>();

    }

    public void readBin(FileInputStream fStream) throws IOException {

        boolean EOF = false;
        DataInputStream dStream = new DataInputStream(fStream);
        int count = 0;
        int operation = 0;
        while (!EOF) {
            try {
                operation = dStream.readInt();
                codeStream[count] = operation;
                count++;
            } catch (EOFException e) {
                EOF = true;
                return;
            }
        }
    }

    public void execute() {
        while (run) // the old fetch-execute cycle
        {
            getNextInstruction();
            decodeAndRunInstruction();
        }
    }

    public void getNextInstruction() {
        ir = codeStream[pc++]; // fetching is straighforward
    }

    public void decodeAndRunInstruction() {
        int instr = ir >> 16; // pull of the opcode and the operands
        int operand = ir & 0xFFFF;
        System.out.println("op: " + instr + " | " + operand);

        runInstruction(instr, operand);
    }

    public void runInstruction(int instr, int operand)
    {
        switch (instr) // what we do depends on what opcode we have
        {
        case HALT:
            // stop execution
            System.err.println("Halting Program");
            run = false;
            break;
        case PUSH:
            // push an integer constant on the stack
            System.err.println("Push constant of " + operand + " to stack");
            stack.push(operand);
            break;
            
        case RVALUE:
            // push the contents of variable to stack
            System.err.println("Push variable " + operand + " to stack");
            stack.push(operand);
            break;
        case LVALUE:
            // push the address of the variable to stack
            System.err.println("Push address of " + operand+ " to stack");
            stack.push(data[operand]);
            // stack.push(operand);
            break;
        case POP:
            // throw away the top value on the stack
            int popped = stack.pop(); 
            System.out.println("Popped " + popped + " from stack");
            break;

        case STO:
            // the rvalue on top of the stack is place in the lvalue below it and both are popped
            rvalue = stack.pop();
            lvalue = stack.pop();
            data[lvalue] = rvalue;
            System.out.println("Store " + rvalue + " at address " + data[lvalue]);
            break;  

        case COPY:
            // push a copy of the top value on the stack
            rvalue = stack.peek();
            stack.push(rvalue);
            System.err.println("Copy " + rvalue);
            break;

        case ADD:
            // pop the top two values off the stack, add them, and push the result
            rvalue = stack.pop();
            lvalue = stack.pop();
            int add = (rvalue+ lvalue);
            stack.push(add);
            System.out.println(rvalue + " + " + lvalue + " = " + add );
            break;

        case SUB:
        // pop the top two values off the stack, subtract them, and push the result
            rvalue = stack.pop();
            lvalue = stack.pop();
            int sub = (rvalue - lvalue);
            stack.push(sub);
            System.out.println(rvalue + " - " + lvalue + " = " + sub);
            break;

        case MPY:
        // pop the top two values off the stack, multiply them, and push the result
            rvalue = stack.pop();
            lvalue = stack.pop();
            int mpy = (rvalue * lvalue);
            stack.push(mpy);
            System.out.println(rvalue + " * " + lvalue + " = " + mpy);
            break;

        case DIV:
            // pop the top two values off the stack, divide them, and push the result
            rvalue = stack.pop();
            lvalue = stack.pop();
            if (lvalue == 0) {
                System.out.println("Error: Can not divide by zero! :(");
                break;
            }
            int div = (rvalue / lvalue);
            stack.push(div);
            System.out.println(rvalue + " / " + lvalue + " = " + div);
            break;

        case MOD:
        // pop the top two values off the stack, compute the modulus, and push the result
            rvalue = stack.pop();
            lvalue = stack.pop();
            int mod = (rvalue % lvalue);
            stack.push(mod);
            System.out.println(rvalue + " % " + lvalue + " = " + mod);
            break;

        case NEG:
        // pop the top value off the stack, negate it, and push the result
            rvalue = stack.pop();
            int neg = (rvalue * -1);
            stack.push(neg);
            System.out.println("neg " + rvalue + " = " + neg);
            break;

        case NOT:
            // pop the top value off the stack, invert all the bits, and push the result
            rvalue = stack.pop();
            int not = ~rvalue;
            stack.push(not);
            System.out.println("not " + rvalue + " = " + not);
            break;

        case OR:
            // pop the top two values off the stack, compute the logical OR, and push the result
            rvalue = stack.pop();
            lvalue = stack.pop();
            if(rvalue != 0 || lvalue != 0){
                stack.push(1);
            }else{
                stack.push(0);
            }
            System.out.println(rvalue + " || " + lvalue + " = " + (rvalue != 0 || lvalue != 0));
            break;
        case AND:
            // pop the top two values off the stack, compute the logical AND, and push the result            
            rvalue = stack.pop();
            lvalue = stack.pop();
            if(rvalue != 0 && lvalue != 0){
                stack.push(1);
            }else{
                stack.push(0);
            }
            System.out.println(rvalue + " && " + lvalue + " = " + (rvalue != 0 && lvalue != 0));
            break;
        case EQ:
            // pop the top two values off the stack, compare them, and push a 1 if they are equal, and a 0 if they are not
            rvalue = stack.pop();
            lvalue = stack.pop();
            if (rvalue == lvalue) {
                stack.push(1);
            } else {
                stack.push(0);
            }
            System.out.println(rvalue + " == " + lvalue + " = " + (rvalue == lvalue));
            break;

        case NE:
            // pop the top two values off the stack, compare them, and push a 1 if they are not equal, and a 0 if they are equal
            rvalue = stack.pop();
            lvalue = stack.pop();
            if (rvalue != lvalue) {
                stack.push(1);
            } else {
                stack.push(0);
            }
            System.out.println(rvalue + " != " + lvalue + " = " + (rvalue != lvalue));
            break;
        case GT:
            // pop the top two values off the stack, compare them, and push a 1 if the first operand is greater than the second, and a 0 if it is not 
            rvalue = stack.pop();
            lvalue = stack.pop();
            if (rvalue > lvalue) {
                stack.push(1);
            } else {
                stack.push(0);
            }
            System.out.println(rvalue + " > " + lvalue + " = " + (rvalue > lvalue));
            break;

        case GE:
            // pop the top two values off the stack, compare them, and push a 1 if the first operand is greater than or equal to the second, and a 0 if it is not 
            rvalue = stack.pop();
            lvalue = stack.pop();
            if (rvalue >= lvalue) {
                stack.push(1);
            } else {
                stack.push(0);
            }
            System.out.println(rvalue + " >= " + lvalue + " = " + (rvalue >= lvalue));
            break;

        case LT:
            // pop the top two values off the stack, compare them, and push a 1 if the first operand is less than the second, and a 0 if it is not 
            rvalue = stack.pop();
            lvalue = stack.pop();
            if (rvalue < lvalue) {
                stack.push(1);
            } else {
                stack.push(0);
            }
            System.out.println(rvalue + " < " + lvalue + " = " + (rvalue < lvalue));
            break;

        case LE:
            // pop the top two values off the stack, compare them, and push a 1 if the first operand is less than or equal to the second, and a 0 if it is not 
            rvalue = stack.pop();
            lvalue = stack.pop();
            if (rvalue <= lvalue) {
                stack.push(1);
            } else {
                stack.push(0);
            }
            System.out.println(rvalue + " <= " + lvalue + " = " + (rvalue <= lvalue));
            break;
        case LABEL:
            //  serves as the target of jumps to n; has no other effect
            // not implemented
            System.out.println("Label has no effect");
            break;
        case GOTO:
            // the next instruction is taken from statement with label n
            pc = operand;
            System.out.println("GOTO " + pc);
            break;
        case GOFALSE:
            // pop the top value; jump if it is zero
            rvalue = stack.pop();
            if (rvalue == 0) {
                pc = operand;
            }
            System.out.println("GOFALSE " + (rvalue == 0));
            break;
        case GOTRUE:
            // pop the top value; jump  if it is nonzero
            rvalue = stack.pop();
            if (rvalue != 0) {
                pc = operand;
            }
            System.out.println("GOTRUE " + (rvalue != 0));
            break;
        case PRINT:
            // pop the top value off the stack and display it as a base 10 integer
            rvalue = stack.pop();
            System.out.println("Top of Stack: " + rvalue);
            break;
        case READ:
            // read a base 10 integer from the keyboard and push its value on the stack
            Scanner keyboard = new Scanner(System.in);
            System.out.println("Enter a base 10 integer: ");
            rvalue = keyboard.nextInt();
            stack.push(rvalue);
            System.out.println("Pushed " + rvalue + " to the stack");
            break;

        case GOSUB:
            // push the current value of the program counter on the call stack and transfer control to the      statement with label 'l'
            callStack.push(pc);
            System.out.println("SubProgram: pushed " + pc + " to callstack, pc is now " + operand);
            pc = operand;
            break;
        case RET:
            // pop the top value off the call stack and store it in the program counter
            pc = stack.pop();
            System.out.println("Return: pc is now " + pc);
            break;

        case ORB:
            // pop the top two values off the stack, compute the bitwise OR, and push the result
            rvalue= stack.pop();
            lvalue= stack.pop();
            int orb = (rvalue | lvalue);
            stack.push(orb);
            System.out.println(rvalue + " | " + lvalue + " = " + orb);
            break;

        case ANDB:
            // pop the top two values off the stack, compute the bitwise AND, and push the result
            rvalue= stack.pop();
            lvalue = stack.pop();
            int andb = (rvalue & lvalue);
            stack.push(andb);
            System.out.println(rvalue + " & " + lvalue + " = " + andb);
            break;

        case XORB:
            //pop the top two values off the stack, compute the bitwise XOR, and push the result
            rvalue= stack.pop();
            lvalue= stack.pop();
            int xorb = (rvalue^ lvalue);
            stack.push(xorb);
            System.out.println(rvalue + " ^ " + lvalue + " = " + xorb);
            break;

        case SHL:
            // pop the top value off the stack, logical shift the bits left by 1 bit, and push the result
            rvalue = stack.pop();
            int shl = rvalue << 1;
            stack.push(shl);
            System.out.println(rvalue + " << 1 = " + shl);
            break;

        case SHR:
            rvalue = stack.pop();
            int shr = rvalue >> 1;
            stack.push(shr);
            System.out.println(rvalue + " >> 1 = " + shr);
            break;

        case SAR:
            rvalue= stack.pop();
            int sar = rvalue >>> 1;
            stack.push(sar);
            System.out.println(rvalue + " >>> 1 = " + sar);
            break;

        default: // oops!
            System.err.println("Opcode not implemented");
            System.exit(instr);
        }
        if (ir == 0)
            run = false; // Isn't this redundant?  Oh, well leave it in for now
    }

    public static void main(String[] args) {

        String fileName = "";
        FileInputStream fileStream;
        
        if (args.length > 0) {
            fileName = args[0];
        } else {
            System.out.println("No file name provided");
            return;
        }

        StackEmulator vm = new StackEmulator(); // create our virtual stack machine

        try {
            fileStream = new FileInputStream(fileName);
            System.out.println("Beginning Execution...");
            vm.readBin(fileStream);
            fileStream.close();
        } catch (Exception e) {
            System.out.println(e);
        }

        vm.execute(); // and, let it go, let it go .....
        System.out.println("Done");
    }

}
