import sqlite3
import time

from update_table import update_table


def set_random_value_in_electrical_sensors_table(database_path: str, update_interval: int, update_column_name: str, min_random_value: int or float, max_random_value: int or float) -> None:
    try:
        sqlite_connection = sqlite3.connect(database_path)
        cursor = sqlite_connection.cursor()

        while True:
            time.sleep(int(update_interval))
            update_table(sqlite_connection, cursor, update_column_name, min_random_value, max_random_value)
            # Обновим еще и состояние
            update_table(sqlite_connection, cursor, 'state', 0, 1)

    except sqlite3.Error as error:
        print('Возникла ошибка при попытке подключения к sqlite3', error)

    finally:
        if (sqlite_connection):
            sqlite_connection.close()
            print('Соединение с sqlite3 закрыто')