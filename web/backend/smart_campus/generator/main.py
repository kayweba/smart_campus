import json

from generator.set_random_value_in_electrical_sensors_table import set_random_value_in_electrical_sensors_table

# if __name__ == "__main__":   
def generator(activated: bool, interval: int = 0.2):
    interval_seconds = interval / 1000
    with open('generator/settings.json') as jsonFileForDump:
        data = json.load(jsonFileForDump)
        data['activated'] = activated
        data['update_interval'] = interval_seconds
    
    with open('generator/settings.json', 'w') as jsonFileForWrite:
        json.dump(data, jsonFileForWrite)
        
              
    database_path: str = data["database_path"]
    update_column_name: str = data["update_column_name"]
    min_random_value: int or float = data["min_random_value"]
    max_random_value: int or float = data["max_random_value"]
    
    set_random_value_in_electrical_sensors_table(database_path, update_column_name, min_random_value, max_random_value)