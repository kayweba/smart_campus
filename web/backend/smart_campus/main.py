from msilib.schema import Error
from fastapi import FastAPI
from fastapi.middleware.cors import CORSMiddleware

import sqlite3

app = FastAPI()
database = r"D:/Learning/SARFTI/begunov_avtomatizaciya/web/db/SmartCampus.sqlite"

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
async def get_rooms_data():
    try:
        connection = sqlite3.connect(database)
        cursor = connection.cursor()

        # Получили данные о комнататх
        cursor.execute(''' 
                        select r.desctiption, count(es.id), r.id
                        from Rooms r
                        join ElectricalSensors es on r.id = es.room_id
                        join ElectricalSensorType est on est.id = es.type_id
                        group by r.desctiption 
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
                        join ElectricalSensorType est on est.id = es.type_id 
                        where es.room_id = {id}
                      ''') 
        
        result = cursor.fetchall()
        return result
    except sqlite3.Error as error:
        print("Ошибка при работе с SQLite", error)
    finally:
        if connection:
            connection.close()
            print("Соединение с SQLite закрыто")
