void main (void)
{
    char arryb[100];
    f(arryb); // *arrybで渡す

    // return も配列にはできない。先頭アドレスが返ってきているだけ

    /* 実はこれはエイリアス
    arryb[0] = 42
    // *(arryb + expr)
    // *(&arryb + expr)
    0[arryb] = 42
    */

    int x;
    x = 42;
    g(x)
}

