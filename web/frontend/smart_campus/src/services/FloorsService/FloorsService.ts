import { FloorsModel } from "../../models/FloorModel";
import { Rooms, RoomsSet } from "../../models/SmartKampusModel";
import { FloorsServiceInterface } from "./FloorsServiceInterface";

// TODO: Доделать сервис и компоненты
export class FloorsService implements FloorsServiceInterface {

    private requsetInit = {
        method: 'GET',
        headers: { "Content-Type": "application/json" },
    }

    // TODO: вынести baseURL в env файл
    private baseURL: string = 'http://localhost:8000/'

    public async getFloorsDataByBuildingId(buildingId: number): Promise<FloorsModel> {
        let resultRecord = {} as FloorsModel
        let resultArray = [] as RoomsSet
        let roomsStringSet = [] as Array<string>
        try {
            // Получаем ответ и преобразуем ответ в пару ключ-значение. Ключ - номер этажа, а значение - набор комнат
            const response = await fetch(this.baseURL + `getFloorsDataByBuildingId?building_id=${buildingId}`, this.requsetInit)
            return response.json()
            .then(data => {
                for (let i in data) {
                    let obj = {} as Rooms

                    obj.name = data[i][0]
                    obj.electrical_sensors_count = data[i][1]
                    obj.id = data[i][2]
                    obj.room_number = data[i][3]

                    roomsStringSet.push(data[i][3].toString()[0])
                    resultArray.push(obj)
                }

                roomsStringSet = roomsStringSet.filter((element, index) => {
                    return roomsStringSet.indexOf(element) === index
                })

                for (let index in roomsStringSet) {
                    const filteredResultArrayByRoomIndex = resultArray.filter(element => {
                        return element.room_number.toString()[0] === roomsStringSet[index]
                    })
                    resultRecord = {
                        ...resultRecord,
                        [roomsStringSet[index]]: filteredResultArrayByRoomIndex
                    }
                }

                return resultRecord
            })


        } catch(error) {
            console.error('ОШИБКА', error);
            
            return {'': []} as FloorsModel
        }
    }
}