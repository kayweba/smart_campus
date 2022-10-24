import json

from set_random_value_in_electrical_sensors_table import set_random_value_in_electrical_sensors_table

if __name__ == "__main__":   
    settings_file: json = json.load(open('settings.json', 'r'))
    
    database_path: str = settings_file["database_path"]
    update_interval: int = settings_file["update_interval"]
    update_column_name: str = settings_file["update_column_name"]
    min_random_value: int or float = settings_file["min_random_value"]
    max_random_value: int or float = settings_file["max_random_value"]
    
    set_random_value_in_electrical_sensors_table(database_path, update_interval, update_column_name, min_random_value, max_random_value)
