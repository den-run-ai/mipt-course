## Установка необходимых пакетов (Ubuntu) ##
```
sudo apt-get install -y subversion cmake make g++ lcov valgrind
```

# Как скачать код #
```
svn checkout https://mipt-course.googlecode.com/svn/trunk/ mipt-course --username MYUSERNAME@gmail.com
```
**Если svn будет спрашивать некий пароль, нужно использовать указанный [тут](http://code.google.com/hosting/settings), а не пароль от своего GMail.**

Код также можно [посмотреть online](http://code.google.com/p/mipt-course/source/browse/), вместе с [историей изменений](http://code.google.com/p/mipt-course/source/list).

# Сборка #
  * Для Debug сборки необходимо выполнить следующие команды из корневой директории проекта:
```
mkdir debug
cd debug
cmake ..
make -j3
```
  * Для Release сборки:
```
mkdir release
cd release
cmake -DCMAKE_BUILD_TYPE=Release ..
make -j3
```
Про другие типы сборки: [docs](http://cmake.org/Wiki/CMake_Useful_Variables).

## Запуск тестов ##
C++, в папке где делалось cmake & make:
```
make test
# или
./base_tests
./sandbox_tests
```

Python, в папке `pysandbox`
```
make test
```

# Структура репозитория #
## Модули ##
  * base/ - различные удобные обертки для работы с файлами, потоками, ...
  * sandbox/ - "детская песочница", в которой можно работать над учебными задачами в первом семестре
  * pysandbox/ - то же, но для любителей Python

## Список third-party библиотек и их лицензии ##
  * googlemock - BSD
  * protobuf - BSD