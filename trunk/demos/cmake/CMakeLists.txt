# Использование:
#  mkdir build  # Обычно сборку делают в отдельной директории.
#  cd build
#  cmake ..
#  make
#  ./helloworld

cmake_minimum_required(VERSION 2.6)

# В простых случаях CMake работает просто замечательно!
# 1. Указываем имя проекта:
project(CMakeDemo)

# 2. Перечисляем файлы исходного кода:
set (SOURCES
     main.cpp
     hello.cpp
     world.cpp
)

# Зависимость от нужных header-файлов получается автоматически,
# при этом регенерировать проект не нужно!

# 3. Указываем имя исполняемого файла, который нужно скомпилировать:
add_executable(helloworld ${SOURCES})
