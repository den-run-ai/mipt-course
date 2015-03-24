Для того, чтобы узнать данные по code coverage для нашего проекта необходимо выполнить следующие шаги:

Установить пакет lcov:
```
sudo apt-get install lcov
```

### Cборка проекта ###
Нужно создать папку, в которую будет помещена специальная Coverage-сборка, и в ней собрать проект:

```
mkdir Coverage
cd Coverage
cmake -DCMAKE_BUILD_TYPE=Coverage ..
make build
```

### Запуск ###
Запускаем тесты/программу по-обычному:
```
./sandbox_tests
```

Собираем статистику по исполненному коду:
```
make extract_coverage
```

После этого появится подпапка `CoverageResults`, в которой лежит много файлов.<br>
Статистику покрытия можно посмотреть так:<br>
<pre><code>google-chrome CoverageResults/index.html<br>
</code></pre>

Для сброса статистики и удаления этой папки нужно выполнить команду:<br>
<pre><code>make reset_coverage<br>
</code></pre>