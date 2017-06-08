                  //Диффиринциатор
/* вместо N подставляем числа , а вместо остальных букв операции */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <io.h>
#include <ctype.h>
#include <assert.h>

#define MAX_STR_LEN 100
#undef _DEBUG

#ifdef _DEBUG
    #define DEBUG( op )  { op; }
#else
    #define DEBUG( op )  {}
#endif

#define DEBUG(...) { __VA_ARGS__ ;}

typedef struct Node
{
    int type;
    int op_val;
    double num_val;
    Node* right;
    Node* left;
};

typedef struct Node_header
{
    Node* head;
    int Node_num;
};



char* s = NULL;

Node* Node_ctor (unsigned char type, int op_val, double num_val);
void GetG0(char* str, Node_header head);
Node* GetE();
Node* GetT();
Node* GetD();
Node* GetP();
Node* GetN();



int main()
{

    int i = 0;

    DEBUG (i = 1);

    char str[MAX_STR_LEN] = "";
    scanf("%s",str);

    Node_header* head = (Node_header*) calloc(1, sizeof(Node_header));

    GetG0(str, *head);

    return 0;
}



Node* Node_ctor (unsigned char type, int op_val, double num_val)
{
    Node* This = (Node*) calloc (1, sizeof (Node));

    This->type = type;
    This->op_val = op_val;
    This->num_val = num_val;

    This->right = NULL;
    This->left = NULL;

    return This;
}


void GetG0(char* str, Node_header head)
{
    if (str == NULL)
    {
        assert(!"string not found");
    }
    s = str;

    DEBUG( printf("CALLING E \n") );

    head.head = GetE();

    if (*s != '\0')
    {
        assert(!"ERROR no \\0 that was waited \n");
    }

}


Node* GetE()
{
    DEBUG( printf("CALLING T \n") );
    Node* node1 = GetT();

    while (*s == '+' || *s == '-')
        {
            DEBUG( printf("I'm im + or -  \n") );
            char op = *s;
            s++;

            DEBUG( printf("CALLING T from while \n") );
            Node* node2 = GetT();

            if (op == '+')
            {
                Node* node_op = Node_ctor(OP, ADD, 0);
                DEBUG( printf("I MAKE PLUS  \n") );

                node_op->left = node1;
                node_op->right = node2;
                node1 = node_op;
            }

            if (op == '-')
            {
                Node* node_op = Node_ctor(OP, SUB, 0);
                DEBUG( printf("I MAKE MINUS  \n") );

                node_op->left = node1;
                node_op->right = node2;
                node1 = node_op;
            }
        }
    return node1;
}


Node* GetT()
{
    DEBUG( printf("CALLING D \n") );
    Node* node1 = GetD();

    while (*s == '*' || *s == '/')
        {
            DEBUG( printf("I'm im * or /  \n") );
            char op = *s;
            s++;

            DEBUG( printf("CALLING D from while \n") );
            Node* node2 = GetD();

            if (op == '*')
            {
                Node* node_op = Node_ctor(OP, MUL, 0);
                DEBUG( printf("I MAKE MUL  \n") );

                node_op->left = node1;
                node_op->right = node2;
                node1 = node_op;
            }

            if (op == '/')
            {
                Node* node_op = Node_ctor(OP, DIV, 0);
                DEBUG( printf("I MAKE DIV  \n") );

                node_op->left = node1;
                node_op->right = node2;
                node1 = node_op;
            }
        }
    return node1;
}


Node* GetD()
{
    DEBUG( printf("CALLING P \n"); );
    Node* node1 = GetP();

    while (*s == '^')
        {
            DEBUG( printf("I'm im ^ \n") );
            char op = *s;
            s++;

            DEBUG( printf("CALLING P from while \n") );
            Node* node2 = GetP();


            Node* node_op = Node_ctor(OP, DEG, 0);
            DEBUG( printf("I MAKE DEGREE  \n") );

            node_op->left = node1;
            node_op->right = node2;
            node1 = node_op;

        }
    return node1;
}

Node* GetP()
{
    if (*s == '(' )
    {
        DEBUG( printf("MAMA I AM IN ( HELP  \n") );
        s++;

        DEBUG( printf("CALLING E  \n") );
        Node* node1 = GetE();
        assert( *s == ')' );
        s++;

        return node1;
    }

    if (*s == 'l')
    {
        DEBUG( printf("LOGORIFMUS IN DA HOUSE \n") );
        s++;

        assert(*s == 'n');
        s++;

        assert(*s == '(');
        s++;

        DEBUG( printf("CALLING E FRO LOGORIFM\n") );
        Node* node1 = GetE();

        Node* node_op = Node_ctor(OP, LN, 0);

        node_op->right = node1;

        return node_op;
    }

    return GetN();
}


Node* GetN()
{
    double numb = 0;

    double res = 0;
    while ( '0' <= *s && *s <= '9')
    {

        res = res*10 + (*s -'0');
        s++;
    }

    if (*s == '.')
    {
        s++;
        double res2 = 0;
        int i = 0;
        while ( '0' <= *s && *s <= '9')
        {
            i--;
            res2 = res2 + pow(10, i) * (*s -'0');
            s++;
        }
    }

    numb = res + res2;

    return Node_ctor(NUM, 0, numb);
}


