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




詳解UNIX

fork, dup, dup2, pipeに関して
##.fork   p217
`pid_t  fork(void)`
返り値
親プロセス  新しい子のプロセスID
子プロセス  ０

子プロセスは親プロセスのデータ、ヒープ、スタックかの各空間を複製し、取得するが子プロセスで変数を変更しても親プロセスの変数の値に影響はない。
`if ((pid== fork) < 0)~elseif (pid == 0)`
子プロセスは必ず０が帰るのでif文で0が帰った時に子プロセスのコードを書く、その後子プロセスのIDが帰ってくる親プロセスはelse文で指定して記述する。




##.dup    p59
`int    dup(int fd)`
dup(fd)
fcntl(fd, F_DUPFD, 0)

既存のファイル記述子を複製する。


##.dup2   p59
`int    dup2(int fd, int fd2)`
dup2(fd, fd2)

close(fd2)
fcntl(fd, F_DUPFD, fd2)


dupとforkの違い

##.pipe




execve関数を実行した際にプロセスが終了してしまう。
パイプの実装をする際にどこにデータを保持しておくのか
##.execve p233
`int    execve(const char *path, char *const argv[], char *const exvp[])`


