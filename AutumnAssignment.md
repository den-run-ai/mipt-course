# Что нужно сделать для зачёта в осеннем семестре #

## Основной (TDD) сценарий ##
  1. Подготовка
    * Придумать какую-нибудь несложную, но интересную задачу,
    * Согласовать формулировку со мной (по e-mail),
    * [Создать для неё issue](http://code.google.com/p/mipt-course/issues/entry), если таковой ещё нет;<br>Если есть - поросить меня установить Owner'а.<br>
<ul><li>Создать svn клиент нашего проекта, научиться компилировать код и запускать тесты - см. <a href='http://code.google.com/p/mipt-course/wiki/Building'>инструкцию</a><br />
</li></ul><ol><li>Работа по <a href='http://en.wikipedia.org/wiki/Test-driven_development'>TDD</a>
<ul><li>Написать и согласовать use-cases для своей задачи<br>
</li><li>Написать <code>DISABLED_</code> тесты и <b>потом</b> интерфейс для классов, решающих основной/самый-простой use-case задачи.<br><b>Рекомендации</b>:<br>
<ul><li>Cмотрите чужие файлы из <code>sandbox/</code> в качестве примеров оформления (copyright header, <code>#include</code> и т.д.).<br>
</li><li>В понятие интерфейс <b>не</b> включается секция <code>private</code>, в частности переменные-члены класса!<br>
</li><li><b>С++</b>: для написания кода создайте в папке <code>sandbox/</code> необходимые файлы:<br><code>sandbox/x.h</code>, <code>sandbox/x.cpp</code> и <code>sandbox/x_test.cpp</code> - для задачи "Х".<br>Эти файлы нужно добавить в клиент SVN (<a href='http://code.google.com/p/mipt-course/wiki/SubversionPlayground#Добавление_файла_в_SVN'>`svn add`</a>), и в <code>sandbox/CMakeLists.txt</code> (см. комментарии в файле).<br>
</li><li><b>Python</b>: см. прошлогодние тесты в папке <code>pysandbox/</code>.<br>
</li><li>Если интерфейсов несколько - рекомендуется также подготовить mock'и, чтобы можно было реализовывать интерфейсы независимо.<br>
</li></ul></li><li>Пройти <a href='http://code.google.com/p/mipt-course/wiki/CodeReview'>code review</a>, выполнить commit тестов и интерфейсов,<br>
</li><li>Для каждого интерфейса:<br>
<ul><li>Реализовать интерфейс в той степени, чтобы прошёл один новый тест; удалить у теста префикс <code>DISABLED_</code>.<br>
</li><li>Пройти code review, сделать commit, написать об этом в issue<br>
</li><li>Повторить для ещё одного теста. Если его нет - написать :-)<br>
</li></ul></li><li>Если интерфейсов несколько - написать тесты, которые показывают что модули могут работать совместно<br>
</li><li>Повторить вышеописанные шаги поочерёдно для остальных use-cases<br>
</li><li>Добиться 100% <a href='Coverage.md'>line coverage</a>
</li><li>Когда use-case'ов реализовано достаточно, можно переходить к самому интересному...<br />
</li></ul></li><li>Зачёт<br>
<ul><li>Ответить на пару простых вопросов в личной беседе,<br>
</li><li>Не забыть зачётку!<br>
</li><li>Получить желанный зачёт</li></ul></li></ol>

<h2>Информация для размышления</h2>
<b>Помните: чем раньше начнёте, тем меньше времени займёт review</b>.<br>
В 2011-2012м учебном году успешно весь цикл "идея-зачёт" проходили в среднем за месяц (!).<br>
<br>
<h3>Примеры задач для "основного" сценария</h3>
<ul><li><a href='http://code.google.com/p/mipt-course/issues/list?q=status%3AAvailable'>Open issues без owner'а</a>
</li><li>Написать контейнер или классический алгоритм на графах<br>
</li><li>Доделать <a href='http://code.google.com/p/mipt-course/source/detail?r=169'>ReliableUdpChannel</a>
</li><li>Простые игры: шашки, пятнашки, ...<br>
</li><li><a href='http://code.google.com/p/mipt-course/issues/detail?id=29'>Разбор и вычисление математических выражений</a>
</li><li><a href='http://code.google.com/p/mipt-course/issues/detail?id=21'>FFT</a>
</li><li>Регулярные выражения (см. <a href='http://code.google.com/p/mipt-course/source/browse/trunk/sandbox/pattern_test.cpp'>sandbox/pattern_test.cpp</a>)<br>
</li><li>Простенькую in-memory/file базу данных<br>
</li><li>Сжатие данных (текстовых, графических, звуковых, и т.д.)<br>
</li><li>Шифрование<br>
</li><li><Место для вашего варианта></li></ul>

<h2>Альтернативы</h2>
Альтернативные сценарии (writing tests after code, etc) - пишите, обсудим.<br>
Но лучше основной.<br>
<br>
<h3>Альтернативный сценарий-1</h3>
<ul><li>Смотрите base/, sandbox/<br>
</li><li>Находите так что-то, что недоделано/неправильно/неудобно; например, откровенный баг или плохое <a href='http://code.google.com/p/mipt-course/wiki/Coverage'>покрытие тестами</a>
</li><li><a href='http://code.google.com/p/mipt-course/issues/entry'>Файлите issue</a>, добавляя в cc автора "плохого" кода и меня<br>
</li><li>Уточняете, что над исправлением/доделыванием того кода сейчас никто не работает<br>
</li><li>Пишете тест, показывающий недоделку/баг<br>
</li><li>Исправляете<br>
<b>Важное замечание</b>: вполне может оказаться, что весь код в репозитории идеален и исправлять/доделывать нечего :)