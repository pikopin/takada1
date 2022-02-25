# takada1
scmaシステム実行用リポジトリ

プログラム解説
scmaとはビヨンド５Gや６Gなどで導入が考慮されているNOMA（Non-orthogonal Multiple Access）と呼ばれる通信方式の１種である。
NOMAとは従来よりも多くの人が高速通信を利用できるようになる技術である。従来の通信方式ではユーザーごとに異なる周波数を割り当てることによって個々人の通信を行っている。
例としてテレビのチャンネルが周波数に該当する。テレビでは１つのチャンネルにつき１つのテレビ局がやっているが、周波数も同じで１つの周波数につき１人が通信している。
昨今の通信需要の急激な増加によって限りある周波数では安定した通信を確保できないことが問題になった。これにより１つの周波数を複数人で共有する方法が考えられた。それがNOMAである。
NOMAでは１つの周波数を２，３人で共有することによって従来の２，３倍の通信量を可能にしている。しかし１つのチャンネルを２，３のテレビ局が使っていては通信状況がめちゃくちゃになるように、
通信でも１つの周波数を複数人で使うには無理があり、NOMAはその無理を受信機での複雑な計算処理を行うことで補っている。

今回のscma通信では６名が同時に通信した場合の通信失敗確率を算出するものをプログラミングした。

実行方法
.hと.cppからなるファイルをすべて同じフォルダにダウンロードし、コマンドプロンプトなどで『g++ -o scma scma.cpp』を入力し実行ファイルscma.exeを作成する。
その後『scma 3』と入力すると実行結果が表示される。

実行結果の解説
実行した結果呼び出される数値は通信環境を徐々に良くしていった場合の通信が失敗する確率を表している。
実行結果に表示されるsnrdBの値が大きくなるほど通信環境が良くなる。
更に１つのsnrdBにつき６つの数値が横に連続して表示されるが、それは６人のユーザーそれぞれの通信の失敗する確率を示している。
実行結果よりsnrdBが大きくなるほど全員の失敗確率が低くなり、最終的には0になる様子が今回の結果から観察できる。