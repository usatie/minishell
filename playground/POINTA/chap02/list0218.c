int seq_search(int *a, int n, int key)
{
    int *p-a;

    while (n-- > 0) {
        if (*p == key)
            return p - a;
        else
            *p++; 
    }
    return -1;
}
