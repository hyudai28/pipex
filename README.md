# pipex
If you don't understand japanese, I suggest you use this site.<https://www.deepl.com/>
## 概要
pipeXは42のファーストサークルレベル3に該当する課題です。<br>

シェルを利用するときのように'ls'コマンドや'cd'コマンドをpipexを通して実行することが目的です。


## 実行方法
`make`  
`./pipex ls`  
当然ですがlsコマンド以外も対応してます。

## 考え方
ネタばれ注意  
コマンドライン引数で受けた取ったものをexecve関数に渡します。
