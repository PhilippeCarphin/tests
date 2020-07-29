int array_experiment(int n)
{
    double table[n];
    int i;
    for(i = 0; i < n; i++){
        table[i] = i;
    }
    return n;
}
int main(int argc, char **argv)
{
    array_experiment(argc);
    return 0;
}
