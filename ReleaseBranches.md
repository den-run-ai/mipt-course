# Предисловие #
На данной странице примеры будут приводиться в виде команд SVN.

Вообще, работать с branch'ами в SVN менее удобно, чем в git, но на данной странице разобран пусть и более сложный и неудобный, но более распространённый инструмент.
Для пользователя git работа с ветками является гораздо более частым действием, поэтому предполагается что опытный пользователь сможет без труда применить в git аналоги нижеприведённых команд SVN.

Основные приводимые ниже идеи (что хранить в какой ветке, когда-что-куда переносить и т.д.) не зависят от используемой системы контроля версий.

Предполагается, что структура папок в репозитории выглядит примерно так:
```
Корень
 |- /trunk
 |- /branches
 |    |-- /branch_1
 |    |-- /branch_2
 |    |-- /branch_3
 |
 |- /releases
      |-- /1.0
      |-- /1.1
      ...
      |-- /1.23
```

# Подход "стабильный trunk" #
В `trunk` хранится только стабильный код - тщательно оттестированный, прошедший все возможные review и т.п.<br>

Для изменений кода: добавления новой функциональности, исправления ошибок - другими словами, решения задач, разработчики (или команды разработчиков) создают для каждой такой задачи отдельную ветку:<br>
<pre><code>$ svn copy URL/trunk URL/branches/feature_X -m "Create a branch for a new feature X"<br>
Committed revision BRANCH_POINT.<br>
</code></pre>
Запоминаем номер ревизии <code>BRANCH_POINT</code> для ветки <code>feature_X</code> - например, можно записать её в файл <code>branches/feature_X/BRANCHED_AT</code>.<br>
<br>
Вся работа над задачей теперь ведётся в папке <code>branches/new_feature</code>.<br>
Для экономии дискового пространства разработчик (или команда) может вместо создания нового клиента переключить свои текущие клиенты на работу с веткой:<br>
<pre><code>$ svn switch URL/branches/feature_X<br>
</code></pre>

Если во время решения задачи в <code>trunk</code> попал некоторый код, который хотелось бы использовать (например, другая команда исправила ошибку), то код в ветке можно обновить до новой версии <code>trunk</code>:<br>
<pre><code># Выполнять из папки, синхронизованной с feature_X<br>
$ svn merge URL/trunk<br>
$ svn commit -m "Take the fresh trunk with a fix for bug 42"  # желательно указать ревизию trunk<br>
Commited revision SYNCED_TO.<br>
</code></pre>
После этого заменяем запомненное значение <code>BRANCH_POINT</code> на значение <code>SYNCED_TO</code> (например, записываем в файл <code>BRANCHED_AT</code>), чтобы избежать лишних <i>merge conflict</i>.<br>
<br>
<b>TODO</b>: можно ли делать проще? Если не пользоваться <code>-r BRANCH_POINT:HEAD</code>, то при финальном <code>merge</code> может возникнуть куча merge conflicts.<br>
<br>
Когда задача решена, ветка проходит review и объединяется с <code>trunk</code>:<br>
<pre><code>$ svn switch URL/trunk<br>
$ svn merge -r BRANCH_POINT:HEAD URL/branches/feature_X<br>
$ svn commit -m "Add new feature X"<br>
</code></pre>
(В принципе, провежуточные результаты работы можно вливать в <code>trunk</code> таким же образом)<br>
<br>
Теперь ветку можно удалить:<br>
<pre><code>$ svn rm URL/branches/feature_X -m "The branch is no longer needed"<br>
</code></pre>

Общая схема выглядит примерно так:<br>
<pre><code>trunk<br>
 |<br>
 X  # svn copy creates revision BRANCH_POINT<br>
 |-&gt; feature_X<br>
 |    |<br>
 |    |<br>
 |---&gt;X  # update the branch to trunk via svn merge<br>
 |    |<br>
 |    |<br>
 |---&gt;X  # update the branch to trunk via svn merge<br>
 |    |<br>
 |    /<br>
 X&lt;===   # merge the branch to trunk and remove it<br>
 |<br>
...<br>
</code></pre>

Для выпуска очередной версии продукта пользователям, разработчику достаточно взять текущую версию <code>trunk</code> и скомпилировать инсталлятор.<br>
При этом удобно сделать копию <code>trunk</code> в подпапку <code>releases</code>, чтобы потом можно было легко посматривать код этого релиза:<br>
<pre><code>$ svn copy URL/trunk URL/releases/1.23 -m "Tagging release 1.23. Let's go get some beer?"<br>
</code></pre>

<h1>Подход "разработка ведётся в trunk"</h1>
Если в команде используется <a href='https://code.google.com/p/mipt-course/wiki/CodeReview'>code review перед коммитом</a>, а также применяется <a href='https://code.google.com/p/mipt-course/wiki/BuildbotSetup'>регулярное тестирование</a>, то может оказаться более удобным вести работу прямо в <code>trunk</code>.<br>
<br>
Для подготовки к новому релизу можно, например, периодически создавать новую ветку и присваивать ей некоторый порядковый номер: <code>branches/123</code>.<br>
<br>
Далее, ветка отдаётся на QA (<i>quality assurance</i> - проверка качества): security review, focus group review, beta testers и т.д.<br>
<br>
Если в ходе QA ветки <code>123</code> обнаруживаются ошибки, то они исправляются и в ветке, и в <code>trunk</code>:<br>
<pre><code># Делается в ветке branches/123<br>
$ svn commit -m "Fix bug 42"<br>
...<br>
Commited revision 666.<br>
<br>
# Делается в trunk, если код ещё не претерпел серьёзных изменений<br>
$ svn merge -c 666 URL/branches/123<br>
</code></pre>

В тот момент, когда делается очередной релиз из ветки <code>123</code>, создаётся новая ветка в папке <code>releases</code>, например <code>releases/2.0.123.0</code>.<br>
Если в этом релизе находят какие-нибудь ошибки, то после их исправления в ветке <code>123</code> можно сделать новый релиз <code>releases/2.0.123.1</code>.<br>
<pre><code>trunk<br>
 |<br>
 X<br>
 |-&gt; 123 # send to QA<br>
 |    |<br>
 |---&gt;X  # merge bugfixes after QA<br>
 |    |  # send to QA again<br>
 |    |<br>
 |    X  # QA approved to publish a beta version<br>
 |    |-&gt; 2.0.123.0 (beta)<br>
 |    |<br>
 |---&gt;X  # merge fixes for bugs found in beta<br>
 |    |<br>
 |    X  # publish a stable version<br>
 |    |-&gt; 2.0.123.1 (stable)<br>
 |    |<br>
...  ...<br>
</code></pre>
Ветка <code>123</code> продолжает существовать, пока не потеряет актуальность.<br>
<br>
Такой подход позволяет поддерживать сразу несколько актуальных релизов, как делают, например:<br>
<ul><li>Microsoft Windows (одновременно сосуществуют разные поколения: Vista SP1, SP2, Windows 7, 7 SP1, ...; разные продуктовые линейки: серверная, десктопная)<br>
</li><li>Ubuntu (LTS версия 10.04, свежая версия 11.04)<br>
</li><li>Chromium (dev, beta, stable версии)</li></ul>

<h1>Послесловие</h1>
Два вышеописанных подхода можно совместить (например, вести основную работу в trunk, но некоторые экспериментальные наработки вести в отдельных ветках).<br>
<br>
В принципе, ветки в SVN являются лишь папками. Поэтому, конкретные варианты наименований и расположений веток и релизов в каждом проекте может быть своё. По этой же причине существует ряд других подходов в ведению веток и релизов.<br>
(Напишите мне известный Вам интересный вариант?)<br>
<br>
<h1>Почитать</h1>
<ul><li>Рекомендации по веткам для Agile команд - <a href='http://www.infoq.com/articles/agile-version-control'>http://www.infoq.com/articles/agile-version-control</a>
</li><li>Пример системы веток и конкретные команды <code>git</code> для работы с ними - <a href='http://habrahabr.ru/blogs/Git/106912/'>http://habrahabr.ru/blogs/Git/106912/</a>