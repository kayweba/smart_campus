def get_count_rows_in_table() -> str:
    return '''select count(id)
    from ElectricalSensors
    '''