#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct{
    double *date;   // 数组指针
    int top;    // 栈顶指针
    int size;   // 栈的大小
}Stack;

//初始化栈
void initStack(Stack *s, int size){
    s->date = (double*)malloc(sizeof(double) * size);   //动态分配数字内存
    s->top = -1;
    s->size = size;
}

//判断栈是否为空
int isEmpty(Stack *s){
    return s->top == -1;
}

//判断栈是否已满
int isFull(Stack *s){
    return s->top == s->size - 1;
}

//入栈
void push(Stack *s, double value){
    if(isFull(s)){  // 检查栈是否已满
        printf("Stack overflow\n");
        exit(1);    // 若栈已满，则退出程序
    }

    s->top++;
    s->date[s->top] = value;
}

//出栈
double pop(Stack* s){
    if (isEmpty(s)){    // 检查栈是否为空
        printf("Stack underflow\n");
        exit(1);    // 若栈为空，则退出程序
    }
    double value = s->date[s->top];
    s->top--;
    return value;
}

//获取栈顶元素
double top(Stack* S){
    if (isEmpty(S)){
        printf("Stack underflow\n");
        exit(1);
    }
    return S->date[S->top];
}

//判断是否为运算符
int isOperator(char c){
    return c == '+' || c == '-' || c == '*' || c == '/';
}
//获取运算符优先级
int getPriority(char op){
    switch (op){
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 2;
    default:
        return 0;
    }
}

//四则运算
double operate(double num1, double num2, char op){
    switch (op) {
    case '+':
        return num1 + num2;
    case '-':
        return num1 - num2;
    case '*':
        return num1 * num2;
    case '/':
        return num1 / num2;
    default:
        printf("Invalid operator:%c\n", op);
        exit(1);
    }
}

//计算后缀表达式的值
double evaluate(char* postfix){
    Stack s;
    initStack(&s, 100); //初始化栈

    char* p = postfix;  //用指针遍历后缀表达式
    while(*p != '\0'){  // 如果当前位置不为空
        if(isdigit(*p)){    // 如果当前位置是数字
            double num = *p - '0';  //获取数字的整数部分
            p++;
            while(isdigit(*p) || *p == '.'){    //继续读取小数部分
                if(*p == '.'){  //如果当前位置是小数点
                    p++;
                    double frac = 0.1;  //初始化分数
                    while(isdigit(*p)){ //继续读取小数部分
                        num += (*p - '0') * frac;   //添加小数部分
                        p++;
                        frac /= 10; //往后分数部分减小10倍
                    }
                    break;  //跳出读取小数值的循环
                }
                else{   //如果不是小数点，表示当前位置是数字，即该部分的数字是一个大于两位数的数字
                    num = num * 10 + (*p - '0');    //计算数字值
                    p++;
                }
            }
            push(&s,num);   //数字入栈
        }
        else if(*p == '+' || *p == '-' || *p == '*' || *p == '/' ){ //如果当前位置是运算符
            double num2 = pop(&s);  //从栈中弹出栈顶元素作为第二个操作数
            double num1 = pop(&s);  //再从栈中弹出栈顶元素作为第一个操作数
            double result = operate(num1, num2, *p);    //利用operate函数计算结果
            push(&s, result);   //将结果压入栈中
            p++;
        }
        else{
            p++;
        }
    }
    
    double value = pop(&s);
    return value;   //返回栈顶元素，即为最终结果
}

//将中缀表达式转换为后缀表达式
void infixToPostfix(char* infix, char* postfix){
    Stack s;
    initStack(&s, 100);

    char* p = infix;    //使用指针遍历中缀表达式
    char* q = postfix;  //使用指针存储后缀表达式
    while(*p != '\0'){  //如果当前位置不为空
        if(isdigit(*p)){    //如果当前位置是数字
            while(isdigit(*p) || *p == '.'){
                *q = *p;    //直接输出
                q++;
                p++;
            }
            *q = ' ';
            q++;
        }
        else if(*p == '+' || *p == '-' || *p == '*' || *p == '/' ){ //如果当前位置是运算符
            int priority1 = getPriority(*p);    //获取当前位置运算符的优先级
            while(!isEmpty(&s) && isOperator(top(&s)) && getPriority(top(&s)) >= priority1){
                //如果栈不空，栈顶为运算符，并且栈顶运算符的优先级大于等于当前运算符的优先级
                char op = pop(&s);
                *q = op;    //将弹出的运算符输出到后缀表达式中
                q++;
                *q = ' ';   //输出空格
                q++;
            }
            push(&s, *p);   //将当前运算符入栈
            p++;
        }
        else if(*p == '('){ //如果当前位置是左括号
            push(&s, *p);   //将其入栈
            p++;
        }
        else if(*p == ')'){ //如果当前位置是右括号
            while(!isEmpty(&s) && top(&s) != '('){  //不断将栈中的元素弹出，直到遇到左括号
                char op = pop(&s);
                *q = op;    //将弹出的运算符输出到后缀表达式中
                q++;
                *q = ' ';   //输出空格
                q++;
            }
            if(!isEmpty(&s) && top(&s) == '('){ //如果栈不空且栈顶元素是左括号
                pop(&s);    //将左括号弹出并丢弃
            }
            else{
                printf("Invalid expression: %s\n", infix);
                exit(1);
            }
            p++;
        }
        else{   //如果当前位置不是数字、运算符、左括号或右括号，直接跳过
            p++;
        }
    }
    while(!isEmpty(&s)){    //如果栈不空，则将栈中所有元素弹出并输出到后缀表达式中
        char op = pop(&s);
        *q = op;
        q++;
        *q = ' ';   //输出空格
        q++;
    }

    *(q - 1) = '\0';    //给后缀表达式添加结束符
}

int main(){
    //测试栈的代码
    // Stack S;
    // initStack(&S,100);
    // push(&S,1);
    // double value = pop(&S);
    // printf("%f",value);
    // return 0;

    char infix[100];
    char postfix[100];

    printf("Enter an infix expression:");
    scanf("%s", infix);

    infixToPostfix(infix, postfix); //将中缀表达式转为后缀表达式
    printf("Postfix notation: %s\n", postfix);

    double result = evaluate(postfix); //计算后缀表达式的值啊
    printf("Result :%g\n", result);

    return 0;
}
