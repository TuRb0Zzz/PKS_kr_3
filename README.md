# Time Tracker (учёт рабочего времени)
Программирование корпоративных систем

## Сборка и запуск

### Требования
- CMake 3.10+
- Компилятор с поддержкой C++17
- Библиотека SQLite3

### Инструкция
```bash
git clone <...> && cd TimeTracker
cmake -S . -B build
cmake --build build
cd build && ./timetracker