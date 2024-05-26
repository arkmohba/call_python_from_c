# call_python_from_c
CからPythonを呼ぶ方法の調査（逆も多分調査する）

## CからPythonを呼び出す

参考: [他のアプリケーションへの Python の埋め込み](https://docs.python.org/ja/3/extending/embedding.html)

* 初期化
  * [Py_Initialize()](https://docs.python.org/ja/3/c-api/init.html#c.Py_Initialize) を呼び出す
* インタプリタを呼び出す方法は以下の通り
  * [PyRun_SimpleString()](https://docs.python.org/ja/3/c-api/veryhigh.html#c.PyRun_SimpleString)
    * Pythonの文字列を直接渡す
  * [PyRun_SimpleFile()](https://docs.python.org/ja/3/c-api/veryhigh.html#c.PyRun_SimpleFile)
    * Pythonのスクリプトファイルのパスを渡す
  * 低水準の操作を呼び出してPythonオブジェクトを構築したり使用することもできる。
    * PyObjectなど？（詳細は未調査）
* CとPythonの間のやり取りが無い、超高水準の埋め込みは以下の手順でできる。
  * Py_SetProgramName(program)
  * Py_Initialize()
  * PyRun_SimpleString("...") or PyRun_SimpleFile("xx.py")
  * Py_FinalizeEx()
  * PyMem_RawFree(program)
* CとPythonの間のやり取りをするためには低水準のインターフェース呼び出しを利用する必要がある。
* CからPythonを呼び出すためには以下を行う必要がある。（データ変換については別途勉強が必要）
  * データ値を C から Python に変換する。
  * 変換された値を使って Python インターフェースルーチンの関数呼び出しを行い
  * 呼び出しで得られたデータ値 Python から C に変換する。
* 低レイヤー
  * Py_Initialize()
  * PyObject* pModule = PyImport_Import(pName);
    * Pythonファイルをモジュールとして呼び込む
  * PyObject* pFunc = PyObject_GetAttrString(pModule, "function name");
    * モジュールのアトリビュートとして関数名から関数オブジェクトを取り出す
  * PyObject* pArgs = PyTuple_New(N)
    * N個の関数引数のデータとしてタプルを用意
  * PyObject* pValue = PyLong_FromLong(i);
  * PyObject* PyTuple_SetItem(pArgs, i, pValue);
    * Cの整数をPythonの整数に変換し、関数引数タプルにセット
  * pValue = PyObject_CallObject(pFunc, pArgs);
    * 関数をコールする
  * int a = PyLong_AsLong(pValue)
    * PythonからCに型を変換する
  * ※Py_DECREFなどの参照削除は省略
  * 
