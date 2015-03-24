Библиотека googletest доступна по адресу http://code.google.com/p/googletest

Здесь приводится лишь краткий список основных интересующих нас возможностей библиотеки.<br>
Полную документацию можно найти по адресу <a href='http://code.google.com/p/googletest/wiki/Documentation'>http://code.google.com/p/googletest/wiki/Documentation</a>

<h1>Компиляция тестов</h1>
<h2>Сборка библиотеки из исходных кодов</h2>
Для начала напишем наш первый тест с использованием библиотеки googletest -<br>
<code>googletest_demo.cpp</code>:<br>
<pre><code>#include &lt;gtest/gtest.h&gt;<br>
<br>
int sum(int a, int b) { return a + b; }  // Функция, которую мы хотим протестировать.<br>
<br>
TEST(MyFunctionTests, Sum) {<br>
  ASSERT_EQ(4 /* ожидаемое значение для */, /* вот этого выражения */ sum(2, 2));<br>
}<br>
</code></pre>

Простая версия сборки:<br>
<pre><code># Выполнять в папке, где лежит googletest_demo.cpp<br>
$ svn checkout http://googletest.googlecode.com/svn/trunk/ googletest<br>
<br>
# Собрать сам gtest и стандартную функцию main()<br>
$ g++ -I googletest -I googletest/include -c -o gtest.a googletest/src/gtest-all.cc<br>
$ g++ -I googletest -I googletest/include -c -o gtest_main.a googletest/src/gtest_main.cc<br>
<br>
# Собрать наши тесты<br>
$ g++ -I googletest/include -c -o googletest_demo.a googletest_demo.cpp<br>
<br>
# Компоновка и запуск.<br>
# ВАЖНО: обратите внимание на -lpthread<br>
$ g++ -o googletest_demo gtest.a gtest_main.a googletest_demo.a -lpthread<br>
$ ./googletest_demo <br>
Running main() from gtest_main.cc<br>
[==========] Running 1 test from 1 test case.<br>
[----------] Global test environment set-up.<br>
[----------] 1 test from MyFunctionTests<br>
[ RUN      ] MyFunctionTests.Sum<br>
[       OK ] MyFunctionTests.Sum (0 ms)<br>
[----------] 1 test from MyFunctionTests (0 ms total)<br>
<br>
[----------] Global test environment tear-down<br>
[==========] 1 test from 1 test case ran. (1 ms total)<br>
[  PASSED  ] 1 test.<br>
</code></pre>

Более сложные варианты интеграции с системами сборки описаны в <a href='http://code.google.com/p/googletest/wiki/Primer#Setting_up_a_New_Test_Project'>в официальной документации</a>,<br>а также в исходных кодах (<a href='http://code.google.com/p/googletest/source/browse/#svn%2Ftrunk%2Fmake'>Makefile</a>, <a href='http://code.google.com/p/googletest/source/browse/#svn%2Ftrunk%2Fcmake'>CMake</a>, <a href='http://code.google.com/p/googletest/source/browse/#svn%2Ftrunk%2Fmsvc'>Visual Studio</a>, <a href='http://code.google.com/p/googletest/wiki/XcodeGuide'>XCode</a>).<br>
<br>
<h2>С использованием системного googletest</h2>
В Ubuntu 10 можно было установить googletest из репозитория.<br>
Сейчас этот метод не рекомендуется, см <a href='http://code.google.com/p/googletest/wiki/FAQ#Why_is_it_not_recommended_to_install_a_pre-compiled_copy_of_Goog'>документацию</a>.<br>
<br>
<h1>Основные приемы работы</h1>
<h2>Семейства макросов ASSERT_XY, EXPECT_XY</h2>
( <a href='http://code.google.com/p/googletest/wiki/Primer#Assertions'>http://code.google.com/p/googletest/wiki/Primer#Assertions</a> )<br>
<br>
Макросы <code>ASSERT_XY</code> и <code>EXPECT_XY</code> проверяют выполнение некоторых условий.<br>
<br>
В случае невыполнения условия макроса ASSERT_XY тест прекращается и начинает выполняться следующий тест:<br>
<pre><code>TEST(MyFunctionTests, Sum) {<br>
  ASSERT_EQ(5, sum(2, 2));<br>
  printf("Код после невыполненного ASSERT_* не выполняется\n");<br>
}<br>
</code></pre>
<pre><code>[ RUN      ] MyFunctionTests.Sum<br>
demo.cpp:6: Failure<br>
Value of: sum(2, 2)<br>
  Actual: 4<br>
Expected: 5<br>
[  FAILED  ] MyFunctionTests.Sum<br>
</code></pre>

В случае невыполнения условия макроса EXPECT_XY тест продолажет выполняться, но в конце все равно будет считаться FAILED:<br>
<pre><code>TEST(MyFunctionTests, Sum) {<br>
  EXPECT_EQ(5, sum(2, 2));<br>
  printf("Код продолжает выполняться после невыполненного EXPECT_*\n");<br>
}<br>
</code></pre>
<pre><code>[ RUN      ] MyFunctionTests.Sum<br>
demo.cpp:6: Failure<br>
Value of: sum(2, 2)<br>
  Actual: 4<br>
Expected: 5<br>
Код продолжает выполняться после невыполненного EXPECT_*<br>
[  FAILED  ] MyFunctionTests.Sum<br>
</code></pre>


Основные макросы: (для каждого <code>ASSERT_XY</code> есть соответствующий <code>EXPECT_XY</code>)<br>
<ul><li><code>ASSERT_TRUE</code>, <code>..._FALSE</code> и т.п. - проверяют true/false<br>
</li><li><code>ASSERT_EQ(ожидаемое_значение, выражение)</code> - проверить, что второй аргумент равен ожидаемому значению (первый аргумент).<br>
</li><li><code>ASSERT_NE(val1, val2);</code> --> проверяет неравенство аргументов,<br><code>..._LT</code> (<),<br><code>..._LE</code> (<=),<br><code>..._GT</code> (>),<br><code>..._GE</code> (>=)<br>
</li><li><code>ASSERT_STREQ(ожидаемая_строка, выражание);</code>, <code>..._STRNE</code>, <code>..._STRCASEEQ</code>, <code>..._STRCASENE</code>
</li><li>Другие, более сложные - <a href='http://code.google.com/p/googletest/wiki/AdvancedGuide#More_Assertions'>http://code.google.com/p/googletest/wiki/AdvancedGuide#More_Assertions</a></li></ul>

Также можно указать дополнительное сообщение для печати в случае невыполнения условий макроса, подобно <code>cout</code> / <code>cerr</code>:<br>
<code>ASSERT_EQ(4, 2 + 2) &lt;&lt; "Что-то не так с математикой?";</code>
<pre><code>example.cpp:6: Failure<br>
Value of: 2 + 2<br>
  Actual: 5<br>
Expected: 4<br>
Что-то не так с математикой?<br>
</code></pre>

<h2>Группы тестов (Test fixtures)</h2>
При написании групп похожих тестов, которым требуется схожая инициализация ресурсов, можно сделать специальный fixture класс, чтобы избежать дубликции кода:<br>
<pre><code>#include &lt;gtest/gtest.h&gt;<br>
#include &lt;stdio.h&gt;<br>
<br>
class Database {<br>
 public:<br>
  Database() { printf("DB created\n"); }<br>
  ~Database() { printf("DB destroyed\n"); }<br>
<br>
  bool Connect() { printf("Connected!\n"); return true; }<br>
  void ReleaseResources() { printf("Released...\n"); }<br>
<br>
  void DoSomething() { }<br>
  void DoSomethingElse() { }<br>
};<br>
<br>
// Создаём новый экземпляр класса Database для каждого теста типа DatabaseTest.<br>
class DatabaseTest : public ::testing::Test {<br>
 protected:<br>
  virtual void SetUp() {<br>
    ASSERT_TRUE(database_.Connect());<br>
  }<br>
<br>
  virtual void TearDown() {<br>
    database_.ReleaseResources();<br>
  }<br>
<br>
  Database database_;<br>
};<br>
<br>
TEST_F(DatabaseTest, DoSomeStuff) {<br>
  database_.DoSomething();<br>
}<br>
<br>
TEST_F(DatabaseTest, DoSomeOtherStuff) {<br>
  database_.DoSomethingElse();<br>
}<br>
</code></pre>
<pre><code>[----------] 2 tests from DatabaseTest<br>
[ RUN      ] DatabaseTest.DoSomeStuff<br>
DB created<br>
Connected!<br>
Released...<br>
DB destroyed<br>
[       OK ] DatabaseTest.DoSomeStuff<br>
[ RUN      ] DatabaseTest.DoSomeOtherStuff<br>
DB created<br>
Connected!<br>
Released...<br>
DB destroyed<br>
[       OK ] DatabaseTest.DoSomeOtherStuff<br>
</code></pre>

<h2>Death-тесты</h2>
Проверяют, что при выполнении указанного выражения программа упадет с определенным сообщением об ошибке:<br>
<pre><code>#include &lt;gtest/gtest.h&gt;<br>
#include &lt;stdio.h&gt;<br>
<br>
int divide(int a, int b) {<br>
  if (b == 0) {<br>
    fprintf(stderr, "Нельзя делить на ноль!\n");<br>
    abort();<br>
  }<br>
  return a / b;<br>
}<br>
<br>
TEST(MyFunctionTests, DivideByZeroDeath) {<br>
  ASSERT_DEATH(divide(42, 0), "делить на ноль");<br>
}<br>
</code></pre>

<h2>Временное отключение тестов</h2>
<b>TODO</b>
Написать про префикс <code>DISABLED_</code> и флаг <code>--gtest_also_run_disabled_tests</code>

<h2>Средства командной строки</h2>
<pre><code>$ ./mytest --gtest_list_tests         # перечислить все имена тестов<br>
$ ./mytest --gtest_repeat=1000        # повторить все тесты 1000 раз<br>
$ ./mytest --gtest_break_on_failure   # поставить breakpoint на нарушение assertions<br>
$ ./mytest --gtest_filter="*Small*"   # запустить только тесты, подходящие под заданный фильтр<br>
$ ./mytest --gtest_filter="-*Death*"  # запустить все тесты, за исключением подходящих под заданный фильтр<br>
</code></pre>

<h2>Random TODOs</h2>
<ul><li>Параллельное/частичное исполнение тестов - sharding