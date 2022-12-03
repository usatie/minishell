#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int globvar = 6;



int main()
{
    int     var;
    pid_t   pid;

    var = 88;
    puts("before vfolk");
    // warning : vfork() is deprecated
    // 関数vforkはforkと同様に新たなプロセスを作成しますが、親のアドレス空間を子にはコピーしません。
    // 子は親のアドレス空間を参照せずに、子はvforkの直後に単にexec(あるいはexit)を呼ぶだけです。
    // 子がexecやexitを呼ぶまで、子は親のアドレス空間で動作します。
    // この最適化で効率が良くなるUNIXシステムの実装もありますが、
    // 子が(vrorkの戻り値を保持する変数以外の)任意のデータを変更したり、関数呼び出しをしたり、execやexitを呼ばずに戻ると、
    // 未定義な結果に至ります


    if ((pid = vfork()) < 0)
    {
        puts("vfork() Error!");
        exit(1);
    }
    else if (pid == 0)
    {
        globvar++;
        var++;
        puts("[child]");
        printf("pid = %ld, ppid = %ld, glob = %d, var = %d\n", (long)getpid(), (long)getppid(), globvar, var);
        _exit(0);
        // Result is indefinite　: exit(0);
        // 標準入出力ストリームをクローズする実装では、標準出力のFILEオブジェクトを表現するメモリをクリアします。
        // 子は親のアドレス空間を借りているわけですから、親が動作を再開してprintfを呼んでも出力は行われずprintfは−1を返します。
    }
    puts("[parent]");
    int ret = printf("pid = %ld, ppid = %ld, glob = %d, var = %d\n", (long)getpid(), (long)getppid(), globvar, var);
    printf("%d\n",ret);
    // 半分くらいの確率で、子のgetppid() != 親のgetpid() になる
    exit(0);
}