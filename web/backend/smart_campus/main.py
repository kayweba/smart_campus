from msilib.schema import Error
from os import curdir
from unicodedata import numeric
from fastapi import FastAPI
from fastapi.middleware.cors import CORSMiddleware

from generator.main import generator

import sqlite3

app = FastAPI()
database = r"D:/Learning/SARFTI/begunov_smart_campus/smart_campus/web/db/korpus_1.db"

origins = [
    "http://localhost:3000",
    "localhost:3000"
]


app.add_middleware(
    CORSMiddleware,
    allow_origins=origins,
    allow_credentials=True,
    allow_methods=["*"],
    allow_headers=["*"]
)


@app.get("/")
async def root():
    return {"message": "Hello world"}

@app.get("/getRoomsData")
def get_rooms_data(id_room: int):
    try:
        connection = sqlite3.connect(database)
        cursor = connection.cursor()

        # Получили данные о комнататх
        cursor.execute(f''' 
                        select r.sdescription, count(es.id), r.id
                        from Rooms r
                        join ElectricalSensors es on r.id = es.id_room
                        join ElectricalSensorType est on est.id = es.id_type
                        where r.building_id = {id_room}
                        group by r.sdescription 
                      ''') 
        
        result = cursor.fetchall()
        return result
    except sqlite3.Error as error:
        print("Ошибка при работе с SQLite", error)
    finally:
        if connection:
            connection.close()
            print("Соединение с SQLite закрыто")


@app.get("/getRoomsElectricalSensorsData")
def get_rooms_electrical_sensors_data(id: int = 1):
    try:
        connection = sqlite3.connect(database)
        cursor = connection.cursor()

        # Получили данные о комнататх
        cursor.execute(f''' 
                        select *
                        from ElectricalSensors es 
                        join ElectricalSensorType est on est.id = es.id_type 
                        join Rooms r on r.id = es.id_room 
                        where es.id_room = {id}
                      ''') 
        
        result = cursor.fetchall()
        return result
    except sqlite3.Error as error:
        print("Ошибка при работе с SQLite", error)
    finally:
        if connection:
            connection.close()
            print("Соединение с SQLite закрыто")

@app.get('/getBuildingsData')
def get_buildings_data():
    try:
        connection = sqlite3.connect(database)
        cursor = connection.cursor()
        
        cursor.execute(f'''
                        select id, 
                               building_number
                               ,description 
                               ,count_of_floors
                        from buildings
                       ''')
        result = cursor.fetchall()
        return result
    except sqlite3.Error as error:
        print('Ошибка при работе с SQLite', error)
    finally:
        if (connection):
            connection.close()
            print("Соединение с SQLite закрыто")
                    
@app.get('/getBuildingSensorsData')
def get_buildings_sensors_data(building_id: int):
    try:
        connection = sqlite3.connect(database)
        cursor = connection.cursor()
        
        cursor.execute(f''' 
                        select es.id as esID, r.sdescription as roomDescription, r.nnumber as roomNumber, es.sname, est.sdescription, es.rvalue, es.nstate 
                        from ElectricalSensors es
                        join ElectricalSensorType est on es.id_type = est.id
                        join Rooms r on es.id_room = r.id
                        where r.building_id = {building_id}
                       ''')
        result = cursor.fetchall()
        return result
    except sqlite3.Error as error:
        print('Ошибка при работе с SQLite закрыто', error)
    finally:
        if (connection):
            connection.close()
            print('Соединение с SQLite закрыто')
        

@app.get('/getFloorsDataByBuildingId')
def get_rooms_by_building(building_id: int):
    try:
        connection = sqlite3.connect(database)
        cursor = connection.cursor()
        
        cursor.execute(f''' 
                        select r.sdescription, count(es.id), r.id, r.nnumber
                        from Rooms r
                        join ElectricalSensors es on r.id = es.id_room
                        join ElectricalSensorType est on est.id = es.id_type
                        where r.building_id = {building_id}
                        group by r.sdescription
                       ''')
        result = cursor.fetchall()
        return result
    except sqlite3.Error as error:
        print('Ошибка при работе с SQLite закрыто', error)
    finally:
        if (connection):
            connection.close()
            print('Соединение с SQLite закрыто')
            
            
@app.get('/startGenerator')
def start_generator(interval: int):
    status: str = ''
    try:
        generator(activated=True, interval=interval)
        status = 'OK'
    except Error:
        status = 'ERROR'
        print(Error)
    return status       
    
@app.get('/stopGenerator')
def stop_generator():
    generator(activated=False)