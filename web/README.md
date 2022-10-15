# Требования к проекту

- Python 3.7^
- Node.js 16.16.0^

## Запуск backend 
Прежде чем выполнять описанные ниже инструкции, в папке `backend/smartkampus` нужно создать виртуальное окружение при помощи **virtualenv**.
Выполните следующие команды:
- `pip install virtualenv` - установит библиотеку, с помощью которой можно развернуть виртуальное окружение
- В папке `backend/smartkampus` выполните команду `virtualenv venv` - создаст виртуальное окружение с именем `venv`
- В этой же папке выполните одну из следующих команд:
    - `venv\Scripts\activate.bat` - активация окружения для Win если запускаете из **cmd**
    - `venv\Scripts\activate.ps1` - активация окружения для Win если запускаете из **powershell**
    - `source venv/bin/activate` для Linux.

В файле `backend/smartkampus/main.py` в переменную `database` необходимо поместить путь до БД.
Не выходя из папки `backend/smartkampus` и находясь в вирутальном окружении, выполните следующие команды:
- `pip install requirements.txt` - установка зависимостей
- `uvicorn main:app --reload` - запуск сервера

Не забудьте выйти из виртуального окружения. Для этого выполните команду `deactivate`.
## Запуск генератора 
Перед запуском генератора откройте файл `utils/generator/settings.json` и в поле `database_path` укажите путь до БД.

Для запуска генератора перейдите в папку `utils/generator` и выполните команду:
- `python main.py` - запуск генератора.

## Запуск frontend

Для старта frontend'а нужно перейти в папку `frontend/smart_campus` и выполнить команду `npm install`, после инсталяции зависимостей выполните команду `npm run start`.
