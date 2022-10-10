import { ElectricalServiceInterface } from './ElectricalServiceInterface'
import { Rooms, RoomsElectrical } from "../../models/SmartKampusModel";

export class ElectricalService implements ElectricalServiceInterface {

    private requsetInit = {
        method: 'GET',
        headers: { "Content-Type": "application/json" },
    }

    // TODO: вынести baseURL в env файл
    private baseURL:string = 'http://localhost:8000/'

    // TODO: Вынести обращение к серверу в отдельный сервис (нап. FetchServer)
    public async getRooms(): Promise<Array<Rooms>> {

        let result = [] as Array<Rooms>
        const response = await fetch(this.baseURL + 'getRoomsData', this.requsetInit) 

       return response.json()
            .then(data => {
                console.log(data);
                
                for (let i in data) {
                    let obj = {} as Rooms

                    obj.name = data[i][0]
                    obj.electrical_sensors_count = data[i][1]
                    obj.id = data[i][2]
                    result.push(obj)
                }             

                return result
            })
    }

    public async getRoomsElectricalSensorsData(id: number): Promise<Array<RoomsElectrical>> {
        let result = [] as Array<RoomsElectrical>

        const response = await fetch(this.baseURL + `getRoomsElectricalSensorsData?id=${id}`, this.requsetInit)

        return response.json()
            .then(data => {               
                for (let i in data) {
                    let obj = {} as RoomsElectrical
                    obj.description = data[i][7]
                    obj.name = data[i][1]
                    obj.state = data[i][3]
                    obj.value = data[i][4]
                    result.push(obj)
                }
                console.log(result);
                
                return result
            })
    }
}