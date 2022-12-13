# minishell

# Man Bash

- login shell
    - 0番目の引数の最初の文字が-であるシェル
    - もしくは--loginオプション付きで起動されたシェルのこと

## sample
## bash実行結果

```
                                                  :
                                                  :exit_status=0

exit                                              :
                                                  :exit_status=0

pwd                                               :/Users/hato/programming/42-CURSUS/code/hello_minishell/playground
                                                  :exit_status=0

invalid command                                   :bash: line 1: invalid: command not found
                                                  :exit_status=127

exit\npwd                                         :
                                                  :exit_status=0

cat Makefile                                      :cat: Makefile: No such file or directory
                                                  :exit_status=1

cat -e Makefile                                   :cat: Makefile: No such file or directory
                                                  :exit_status=1

grep mini Makefile                                :grep: Makefile: No such file or directory
                                                  :exit_status=2

/bin/cat Makefile                                 :cat: Makefile: No such file or directory
                                                  :exit_status=1

./tests/hello.sh                                  :bash: line 1: ./tests/hello.sh: No such file or directory
                                                  :exit_status=127

echo 'hello'                                      :hello
                                                  :exit_status=0

echo "hello"                                      :hello
                                                  :exit_status=0

echo '"hello"'                                    :"hello"
                                                  :exit_status=0

echo "'hello'"                                    :'hello'
                                                  :exit_status=0

     pwd                                          :/Users/hato/programming/42-CURSUS/code/hello_minishell/playground
                                                  :exit_status=0

echo hello'world'"42"                             :helloworld42
                                                  :exit_status=0

ec"ho" he"ll"o                                    :hello
                                                  :exit_status=0

echo hello >hello.txt                             :
                                                  :exit_status=0  out_file=hello.txt


echo hello 1>hello.txt                            :
                                                  :exit_status=0  out_file=hello.txt

cat Makefile | grep minishell                     :cat: Makefile: No such file or directory
                                                  :exit_status=1

cat Makefile | grep c | sort -r                   :cat: Makefile: No such file or directory
                                                  :exit_status=0

cat Makefile | grep c | sort -r > sort.txt        :cat: Makefile: No such file or directory
                                                  :exit_status=0  out_file=sort.txt


cat Makefile | grep l > grep.txt | sort -r        :cat: Makefile: No such file or directory
                                                  :exit_status=0  out_file=grep.txt


echo 111111111111111111111111111111               :111111111111111111111111111111
                                                  :exit_status=0

echo $USER                                        :hato
                                                  :exit_status=0

echo hello$USER                                   :hellohato
                                                  :exit_status=0

echo hello "Mr. "$USER                            :hello Mr. hato
                                                  :exit_status=0

echo "$USER"                                      :hato
                                                  :exit_status=0

echo "Variable with text $USER"                   :Variable with text hato
                                                  :exit_status=0

echo "Variable $USER between text"                :Variable hato between text
                                                  :exit_status=0

echo "Multiple $USER variables $SHELL"            :Multiple hato variables /bin/zsh
                                                  :exit_status=0

echo "Variables non-space $USER.$SHELL+$HOME"     :Variables non-space hato./bin/zsh+/Users/hato
                                                  :exit_status=0

echo "Undefined variable $undefined_variable"     :Undefined variable
                                                  :exit_status=0

echo "These are not variable : $. $+ "            :These are not variable : $. $+
                                                  :exit_status=0

echo "These are variable     : $_foo $foo"        :These are variable     :
                                                  :exit_status=0

echo $?                                           :0
                                                  :exit_status=0

echo "$?"                                         :0
                                                  :exit_status=0

exit\npwd                                         :                                                  :exit_status=0

cat Makefile                                      :cat: Makefile: No such file or directory
                                                  :exit_status=1

cat -e Makefile                                   :cat: Makefile: No such file or directory
                                                  :exit_status=1

grep mini Makefile                                :grep: Makefile: No such file or directory
                                                  :exit_status=2

/bin/cat Makefile                                 :cat: Makefile: No such file or directory
                                                  :exit_status=1

./tests/hello.sh                                  :bash: line 1: ./tests/hello.sh: No such file or directory
                                                  :exit_status=127

echo 'hello'                                      :hello
                                                  :exit_status=0

echo "hello"                                      :hello
                                                  :exit_status=0

echo '"hello"'                                    :"hello"
                                                  :exit_status=0

echo "'hello'"                                    :'hello'
                                                  :exit_status=0

     pwd                                          :/Users/hato/programming/42-CURSUS/code/hello_minishell/playground
                                                  :exit_status=0

echo hello'world'"42"                             :helloworld42
                                                  :exit_status=0

ec"ho" he"ll"o                                    :hello
                                                  :exit_status=0
```

## 定義/使えそうな命名
- blank
    - 空白文字 or tab文字
- word = token
    - 単語
    - 変数名、予約語、演算子、定数
    - shellが1文字とみなす文字の並び
- name = identifier(識別子)
    - 英数字とアンダースコア文字だけから構成される
      かつ、最初の文字が英字かアンダースコア文字である単語
- metacharacter
    - クオートされていない場合に、単語区切りとなる文字
    - `| & ; ( ) < > space tab`
- control operator
    - 制御機能を持つtoken
    - `|| & && ; ;; ( ) | |& <newline>`
- Compound Commands
    - 複合コマンド
- pipeline
    - 制御演算子 | または |& で区切った 1 つ以上のコマンドの並び
- job control
    - プロセスの実行を選択的に停止させ、あとで実行を再開させる機能のこと
- parameter
    - 値を保持するためのもの
      名前、 数字、後述の 特殊なパラメータ で挙げる特殊文字のいずれかで表現される
      シェルでの用法においては、 変数(variable) とは 名前 で表現されたparameter
      変数は値と 0 個以上の属性を持ちます
      属性は declare 組み込みコマンド (後述の シェルの組み込みコマンド の declare の項を参照) で設定されます。
    - `name=[value]`
- Positional Parameters
    - 位置パラメーター
    - 1桁以上の数値で表されるパラメータ
    - 0は含まない
    - 位置パラメータは、シェルが起動されたときにシェルの引き数が代入されますが
      組み込みコマンドの set を使って代入し直すこともできます。
    - 代入文を使って位置パラメータへの代入を行うことはできません
- Special Parameters
    - `*@#?-$!0_`
- single quate
    - `'`
- double quate
    - `"`

- reserved word
    - 以下の単語がクォートされておらず、 
      かつ単純なコマンド (simple command) の 先頭の単語 (後述の シェルの文法 を参照) であるか
      case コマンドや for コマンドの 3 番目の単語である場合
    - `! case do done elif else esac fi for function if in select then until while { } time [[ ]]`


## 文法/機能
### single quote
    - 'で文字を囲むと、 クォート内部のそれぞれの文字は文字としての値を保持します。 
    - シングルクォートの間にシングルクォートを置くことはできません。 これはバックスラッシュを前に付けても同じです。
### double quote
    - ダブルクォートで文字を囲むとクォート内部の全ての文字は文字としての値を 保持しますが、
      $, \`, \ は例外となります。 履歴展開が有効なときには、 ! がこれに加わります。
      $ と \` はダブルクォートの内部でも特殊な意味を失いません。
      バックスラッシュの場合は、次の文字が $, \`, ", \, <newline> のいずれかである場合に限り特殊な意味を失いません。
      前にバックスラッシュを付ければ、 ダブルクォート文字をダブルクォートによるクォートの内部で クォートできます
      履歴展開は有効であれば実行されますが、
      ダブルクォート中の ! がバックスラッシュでエスケープされている場合を除きます。
      ! の前のバックスラッシュは削除されません。

### redirect
### pipe
### $
### $?
### special input
    - ctrl-c
    - ctrl-d
    - ctrl-ja

## built-in
    - echo -n
    - cd (with only a relative or absolute path)
    - pwd (no option)
    - export (no option)
    - unset (no option)
    - env (no option & arg)
    - exit (no option)

## list
- list
    - 1つ以上のパイプラインを演算子 ;, &, &&, || のいずれかで区切って並べたもの
    - パイプラインの最後に ;, &, <newline> のいずれかを置くこともできます

## 複合コマンド (Compound Commands)

    - ダブルクォートで文字を囲むとクォート内部の全ての文字は文字としての値を 保持しますが、 
      $, \`, \ は例外となります。 履歴展開が有効なときには、 ! がこれに加わります。
      $ と \` はダブルクォートの内部でも特殊な意味を失いません。
      バックスラッシュの場合は、次の文字が $, \`, ", \, <newline> のいずれかである場合に限り特殊な意味を失いません。
      前にバックスラッシュを付ければ、 ダブルクォート文字をダブルクォートによるクォートの内部で クォートできます
      履歴展開は有効であれば実行されますが、
      ダブルクォート中の ! がバックスラッシュでエスケープされている場合を除きます。 
      ! の前のバックスラッシュは削除されません。

- $'string'
    - $'string' の形式を持つ単語は特殊な扱いを受けます
      この単語は string に展開され、 それから ANSI C 標準で仕様が決められている、 
      バックスラッシュでエスケープされている文字に置き換えられます。 
      バックスラッシュエスケープシーケンスは、 (もし存在すれば) 以下のようにデコードされます:




### パイプライン
- pipeline
    - 制御演算子 | または |& で区切った 1 つ以上のコマンドの並び
    - command の標準出力は command2 の標準入力にパイプで接続されます
      この接続は、 コマンドで指定したどのリダイレクションよりも先に実行されます (後述の リダイレクト を参照)
      |& を使うと、command の標準エラー出力もパイプを通して command2 の標準入力に接続されます
      これは 2>&1 | の短縮形です
      この標準エラー出力の暗黙のリダイレクションは、 コマンドに指定された全てのリダイレクションの後に実行されます。
    - `[time [-p]] [ ! ] command [ [|||&] command2 ... ]`

