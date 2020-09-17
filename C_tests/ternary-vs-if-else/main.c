
int ternary_max(int a, int b){
    int x;
    x = (a>b ? a : b);
    return x;
}
int if_else_max(int a, int b){
    int x;
    if(a>b){
        x = a;
    } else {
        x = b;
    }
    return x;
}

int main(void){
    int a = 5;
    int b = 9;
    const int x = (a>b?a:b);
    ternary_max(5,9);
    if_else_max(5,9);
}
