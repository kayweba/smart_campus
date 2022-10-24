import random

from get_count_rows_in_table import get_count_rows_in_table
from get_query_for_update import get_query_for_update

def update_table(sqlite_connection, cursor, update_column_name: str, min_random_value: float, max_random_value: int or float):
    cursor.execute(get_count_rows_in_table())
    count_row_in_table = cursor.fetchone()
    cursor.close

    counter: int = 1
    while counter <= count_row_in_table[0]:
        random_value: int
        if update_column_name == 'state':
            random_value: int = random.randint(min_random_value, max_random_value)
        else:
            random_value: int = round(random.uniform(min_random_value, max_random_value), 3)

        cursor.execute(get_query_for_update(random_value, counter, update_column_name))
        sqlite_connection.commit()
        cursor.close

        print('В таблицу "ElectricalSensors" было добавлено значение: ' +
              str(random_value))
        counter += 1