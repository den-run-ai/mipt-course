**Оглавление:**


---


Обычно, начинающим участникам проектов не сразу дается доступ на запись в репозиторий. Но без доступа на запись не так просто разобраться в некоторых командах работы с SVN, поэтому здесь я привожу инструкцию как запустить свой собственный тестовый SVN сервер и поиграться с ним, не боясь никому ничего сломать.

Данная инструкция **не** является примером того, как надо делать `checkout` и `commit` в нашем проекте. Для получения этой информации читайте страницу CodeReview. Все остальные команды можно смело использовать с нашим проектом.

# Предварительная настройка #
Данная страница предполагает, что пользователь работает в ОС Ubuntu Lucid 10.04

```
# Ubuntu - убедиться, что установлен пакет Subversion
sudo apt-get install -y subversion
```

Также проверена работа в Cygwin.

Перед выполнением нижеприведённых шагов, следует добавить строку
```
export EDITOR=мойлюбимыйредактор  # gedit, kate, vim, emacs, notepad
```
в конец файла `~/.bashrc` и перезапустить терминал (или выполнить команду `source ~/.bashrc`)

# Настройка клиента SVN #
Основной интерес в рамках нашего курса представляет работа с клиентом SVN.

Для создания клиента необходимо скачать (checkout) репозиторий с некоторого SVN сервера.<br>
Checkout-инструкции нашего курса описаны <a href='http://code.google.com/p/mipt-course/wiki/Building'>здесь</a>.<br>
<br>
Если Вы хотите "поиграться" с тестовым SVN-сервером или настроить полноценный SVN-сервер для вашего closed-source проекта - см. ниже.<br>
<br>
<h2>Настройка локального сервера SVN для экспериментов</h2>
<i>В основном взято <a href='http://queens.db.toronto.edu/~nilesh/linux/subversion-howto/'>отсюда</a>.</i>

<pre><code>$ cd<br>
$ mkdir svn_sandbox_server<br>
$ cd svn_sandbox_server<br>
$ svnadmin create .<br>
$ $EDITOR conf/svnserve.conf<br>
</code></pre>
Ввести в файл следующее содержимое вместо <b>всего</b> стандартного конфигурационного файла:<br>
<pre><code>[general]<br>
# Don't use this configuration file on a real server - this is NOT secure!<br>
anon-access = write<br>
auth-access = write<br>
password-db = passwd<br>
realm = My Test Repository<br>
</code></pre>
сохранить и выйти.<br>
<br>
Далее,<br>
<pre><code>$ svnserve -d -r .  # Запускает сервер в режиме демона, НЕ добавляя его в автозапуск.<br>
$ cd<br>
$ svn checkout svn://localhost/ svn_sandbox  # у "checkout" есть сокращение - "co"<br>
Checked out revision 0.<br>
$ cd svn_sandbox # Зайти в только что созданного клиента<br>
</code></pre>

<h2>Настройка полноценного сервера</h2>
<a href='https://help.ubuntu.com/community/Subversion'>https://help.ubuntu.com/community/Subversion</a>

<h1>Основные команды SVN</h1>
<h2>Создание клиента</h2>
<pre><code># Различные варианты:<br>
$ svn co URL/some/long/path   # взять самую свежую версию кода по адресу URL в папку path<br>
$ svn co URL/some/long/path local_path  # взять самую свежую версию кода по адресу URL в папку local_path<br>
$ svn co -r REV URL local_path # взять конкретную ревизию REV<br>
...<br>
</code></pre>

<h2>Добавление файла в SVN</h2>
Мы только что создали сервер и клиент, поэтому история в репозитории пустая.<br>
<br>
Чтобы начать некоторую историю, нужно для начала создать какой-то файл.<br>
По умолчанию, Subversion не следит за новыми файлами, созданными в клиенте - чтобы случайно не добавить вашу папку <code>build</code>, файл с паролем или что-нибудь в этом роде.<br>
<br>
Поэтому, создавая новые файлы/папки, их нужно добавить под контроль вручную:<br>
<pre><code># Создаём файл<br>
$ echo "Hello, subversion" &gt;hello.txt<br>
<br>
# Добавляем его в клиент<br>
$ svn add hello.txt<br>
A         hello.txt<br>
<br>
# Отправляем на сервер<br>
$ svn commit hello.txt -m "Adding my first file to SVN"  # Одна из форм команды commit<br>
Adding         hello.txt<br>
Transmitting file data .<br>
Committed revision 1.<br>
</code></pre>

<h2>Просмотр статуса клиента</h2>
<pre><code>$ $EDITOR hello.txt  # добавить восклицательный знак на конце, сохранить и выйти<br>
$ touch mybuild.exe  # допустим при компиляции проекта получается exe файл<br>
$ svn status         # показать статус всех файлов в клиенте<br>
?       mybuild.exe<br>
M       hello.txt<br>
$ svn status -q      # показать статус только добавленных в клиент файлов<br>
M       hello.txt<br>
$ svn diff           # показать все изменения, внесенные в данном клиенте, но не закоммиченные<br>
Index: hello.txt<br>
===================================================================<br>
--- hello.txt	(revision 1)<br>
+++ hello.txt	(working copy)<br>
@@ -1 +1 @@<br>
-Hello, subversion<br>
+Hello, subversion!<br>
# в формате http://en.wikipedia.org/wiki/Unified_diff#Unified_format<br>
<br>
$ svn commit hello.txt  # откроется $EDITOR, куда нужно будет ввести комментарий коммита<br>
Sending        hello.txt<br>
Transmitting file data .<br>
Committed revision 2.<br>
</code></pre>

<h2>Откат локальных изменений</h2>
<pre><code>$ echo "Extra line" &gt;&gt; hello.txt  # добавить лишнюю строчку<br>
$ svn diff<br>
Index: hello.txt<br>
===================================================================<br>
--- hello.txt	(revision 2)<br>
+++ hello.txt	(working copy)<br>
@@ -1 +1,2 @@<br>
 Hello, subversion!<br>
+Extra line<br>
<br>
# Откатить список файлов:<br>
$ svn revert hello.txt<br>
Reverted 'hello.txt'<br>
<br>
# или так - откатить все файлы в папке ("." - текущая папка)<br>
$ svn revert -R .<br>
Reverted 'hello.txt'<br>
</code></pre>

<h2>Просмотр истории</h2>
<pre><code>$ svn log hello.txt  # В случае большой истории целесообразно пользоваться флагом -l ЧИСЛО_КОММИТОВ или перенаправлять вывод в less.<br>
# svn log также поддерживает вывод истории папки.<br>
------------------------------------------------------------------------<br>
r2 | (no author) | 2011-09-30 23:28:58 +0400 (Fri, 30 Sep 2011) | 2 lines<br>
<br>
Add an exclamation mark at the end<br>
<br>
------------------------------------------------------------------------<br>
r1 | (no author) | 2011-09-30 20:51:07 +0400 (Fri, 30 Sep 2011) | 1 line<br>
<br>
Adding my first file to SVN<br>
------------------------------------------------------------------------<br>
</code></pre>

<h3>Построчная история изменений файла</h3>
Здесь нагляднее будет взять какой-нибудь файл, который на самом деле изменяли несколько человек:<br>
<pre><code>$ cd<br>
$ svn checkout -r 100 http://mipt-course.googlecode.com/svn/trunk/base annotate_demo<br>
A    annotate_demo/file_utils.cpp<br>
A    annotate_demo/condition_variable.h<br>
A    annotate_demo/mutex.cpp<br>
A    annotate_demo/file_utils.h<br>
A    annotate_demo/random.h<br>
A    annotate_demo/mutex.h<br>
A    annotate_demo/condition_variable.cpp<br>
A    annotate_demo/target.mk<br>
A    annotate_demo/check_test.cpp<br>
A    annotate_demo/common.h<br>
Checked out revision 100.<br>
$ cd annotate_demo<br>
$ svn annotate common.h  | head    # синоним к annotate - blame<br>
    48   timurrrr // Copyright (c) 2010 Timur Iskhodzhanov and MIPT students. All rights reserved.<br>
     3   timurrrr // Use of this source code is governed by a BSD-style license that can be<br>
     3   timurrrr // found in the LICENSE file.<br>
     4   timurrrr #ifndef BASE_COMMON_H_<br>
     4   timurrrr #define BASE_COMMON_H_<br>
     3   timurrrr <br>
    20   timurrrr #include &lt;stdio.h&gt;<br>
    20   timurrrr #include &lt;stdlib.h&gt;<br>
    82 bochkarev.alex@gmail.com #include &lt;stdint.h&gt;<br>
     3   timurrrr <br>
# Выдает ЦЕЛИКОМ файл, добавляя к каждой строчке файла префикс " РЕВИЗИЯ АВТОР_ПОСЛЕДНЕГО_ИЗМЕНЕНИЯ"<br>
# Имеет смысл перенаправлять вывод команды в less или в файл.<br>
</code></pre>

<h2>Переименование, копирование файлов</h2>
<pre><code>$ svn mv hello.txt myfirstfile.txt<br>
A         myfirstfile.txt<br>
D         hello.txt<br>
$ svn status<br>
D       hello.txt<br>
A  +    myfirstfile.txt<br>
# обратите внимание на "плюсик" - история сохранилась<br>
$ svn commit    # можно вообще не передавать никаких флагов к commit, но так делать не рекомендуется<br>
Deleting       hello.txt<br>
Adding         myfirstfile.txt<br>
<br>
Committed revision 3.<br>
timurrrr@ubuntu-vm:~/svn_sandbox$ svn log myfirstfile.txt <br>
r3: Rename the file<br>
r2: Add an exclamation mark at the end<br>
r1: Adding my first file to SVN<br>
<br>
# ---------------------------------------------<br>
# НЕ НАДО делать так, иначе потеряется история:<br>
$ mv hello.txt myfirstfile.txt <br>
$ svn rm hello.txt<br>
D         hello.txt<br>
$ svn add myfirstfile.txt <br>
A         myfirstfile.txt<br>
</code></pre>

<h2>Удаление файла</h2>
<pre><code>$ svn rm filetodelete.txt<br>
</code></pre>

<h2>Команда update, merge конфликт</h2>
Создадим второго клиента в новом терминале:<br>
<pre><code>$ svn checkout svn://localhost/ svn_sandbox2<br>
A    svn_sandbox_other/myfirstfile.txt<br>
Checked out revision 3.<br>
$ cd svn_sandbox_other/<br>
</code></pre>

Создайте во втором клиенте файл <code>hello.c</code> со следующим содержимым:<br>
<pre><code>#include &lt;stdio.h&gt;<br>
int main(void) {<br>
  printf("Hello, world!\n");<br>
  return 0;<br>
}<br>
</code></pre>
Далее,<br>
<pre><code>$ svn add hello.c <br>
A         hello.c<br>
$ svn commit hello.c -m "Add helloworld program written in C"<br>
</code></pre>

В первом клиенте выполните команду <code>update</code>:<br>
<pre><code>$ svn update  # сокращенная форма: svn up; также можно указать конкретный номер ревизии: -r REV<br>
A    hello.c<br>
Updated to revision 4.<br>
</code></pre>

Теперь, в каждом клиенте поменяем строку, передаваемую <code>printf</code> на какую-нибудь другую, например:<br>
<ul><li>"Hello, my name is Alice\n" - в первом клиенте,<br>
</li><li>"Hello, my name is Bob\n" - во втором клиенте.</li></ul>

Представим себе на минутку, что два разработчика примерно одновременно изменили некоторый кусок кода и разработчик №1 успел сделать <code>commit</code> первым:<br>
<pre><code># В первом клиенте, после изменения строки printf<br>
$ svn commit hello.c -m "My name is Alice"<br>
Sending        hello.c<br>
Transmitting file data .<br>
Committed revision 5.<br>
</code></pre>

Теперь во втором клиенте, после изменения строки printf:<br>
<pre><code>$ svn up<br>
$ svn up<br>
Conflict discovered in 'hello.c'.<br>
Select: (p) postpone, (df) diff-full, (e) edit,<br>
        (mc) mine-conflict, (tc) theirs-conflict,<br>
        (s) show all options:                      # &lt;&lt;&lt; например, введем 'p'<br>
C    hello.c<br>
Updated to revision 5.<br>
Summary of conflicts:<br>
  Text conflicts: 1<br>
# hello.c находится в состоянии "конфликт".<br>
# Subversion создала несколько вспомогательных файлов<br>
$  svn status<br>
?       hello.c.r4     # ревизия №4, на которую был синхронизирован наш клиент до svn up    <br>
?       hello.c.r5     # "серверная" версия ревизии №5, на которую мы обновились<br>
?       hello.c.mine   # локальная версия файла перед svn up<br>
C       hello.c        # объединенная версия файла<br>
</code></pre>
При помощи различных утилит 3-way merge эти файлы можно объединить в одну "новую" версию.<br>
<br>
Можно сделать это и вручную, открыв файл hello.c:<br>
<pre><code>#include &lt;stdio.h&gt;<br>
int main(void) {<br>
&lt;&lt;&lt;&lt;&lt;&lt;&lt; .mine<br>
  printf("Hello, my name is Bob!\n");<br>
=======<br>
  printf("Hello, my name is Alice\n");<br>
&gt;&gt;&gt;&gt;&gt;&gt;&gt; .r5 <br>
  return 0;<br>
}<br>
</code></pre>
Фрагменты "<<<<", "====", ">>>>" были добавлены Subversion.<br>
<br>
Разрешив конфликт вручную (что именно написать вместо конфликта - зависит от специфики кода и изменений):<br>
<pre><code>#include &lt;stdio.h&gt;<br>
int main(void) {<br>
  printf("Hello, we are Alice and Bob!\n");<br>
  return 0;<br>
}<br>
</code></pre>
можно сказать Subversion, что конфликта больше нет:<br>
<pre><code>$ svn diff hello.c <br>
Index: hello.c<br>
===================================================================<br>
--- hello.c	(revision 5)<br>
+++ hello.c	(working copy)<br>
@@ -1,5 +1,5 @@<br>
 #include &lt;stdio.h&gt;<br>
 int main(void) {<br>
-  printf("Hello, my name is Alice\n");<br>
+  printf("Hello, we are Alice and Bob!\n");<br>
   return 0;<br>
 }<br>
$ svn resolved hello.c<br>
Resolved conflicted state of 'hello.c'<br>
$ svn status<br>
M       hello.c<br>
# теперь можно продолжать работу<br>
</code></pre>

<h1>TODO</h1>
<ul><li>утилиты diff, patch<br>
</li><li>визуальные утилиты diff, merge (например, SourceGear DiffMerge)<br>
</li><li>svn externals<br>
</li><li>svn ignore</li></ul>

<h1>Дополнительная информация</h1>
<ul><li><code>svn help</code>, <code>svn help &lt;command&gt;</code>
</li><li><a href='http://svnbook.red-bean.com/en/1.1/ch01s07.html'>http://svnbook.red-bean.com/en/1.1/ch01s07.html</a>