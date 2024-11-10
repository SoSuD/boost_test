# Минимальная версия CMake
cmake_minimum_required(VERSION 3.20)

# Название проекта
project(testboost)

# Укажите путь к Boost
set(BOOST_ROOT "C:/boost_1_86_0")  # Укажите путь к директории Boost
set(Boost_USE_STATIC_LIBS ON)      # Использование статических библиотек
set(Boost_NO_SYSTEM_PATHS ON)      # Игнорирование системных путей Boost

# Настройка путей к библиотекам в зависимости от конфигурации

# Добавьте исполняемый файл
add_executable(testboost "testboost.cpp" "testboost.h" "req.h")

# Установка стандарта C++
if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET testboost PROPERTY CXX_STANDARD 20)
endif()

# Подключение Boost.JSON вручную
target_include_directories(testboost PRIVATE "${BOOST_ROOT}")
target_link_libraries(testboost PRIVATE "${BOOST_JSON_LIBRARY}")
