def get_query_for_update(value: float, id: int, column_name: str) -> str:
    return '''update ElectricalSensors 
    set {column_name} = {value}
    where id = {id};'''.format(value=value, id=id, column_name=column_name)