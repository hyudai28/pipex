# pipex
If you don't understand japanese, I suggest you use this site.<https://www.deepl.com/>
## 概要
pipeXは42のファーストサークルレベル3に該当する課題です。<br>

シェルを利用するときのように'ls'コマンドや'cd'コマンドをpipexを通して実行することが目的です。


## 実行方法
```make```  
```./pipex Makefile cat grep CC```  
当然ですがcatコマンド以外も対応してます。

## 考え方
ネタばれ注意  
コマンドライン引数で受けた取ったものをexecve関数に渡します。

子プロセスは親プロセスのデータ、ヒープ、スタックかの各空間を複製し、取得するが子プロセスで変数を変更しても親プロセスの変数の値に影響はない。
```if ((pid== fork) < 0)~elseif (pid == 0)```
子プロセスは必ず０が帰るのでif文で0が帰った時に子プロセスのコードを書く、その後子プロセスのIDが帰ってくる親プロセスはelse文で指定して記述する。




