import { ElectricalServiceInterface } from './ElectricalServiceInterface'
import { Rooms, RoomsElectrical, RoomsElectricalSet, RoomsSet } from "../../models/SmartKampusModel";

export class ElectricalService implements ElectricalServiceInterface {

    private requsetInit = {
        method: 'GET',
        headers: { "Content-Type": "application/json" },
    }

    // TODO: вынести baseURL в env файл
    private baseURL: string = 'http://localhost:8000/'

    public async getRooms(): Promise<RoomsSet> {

        let result = [] as RoomsSet
        try {
            const response = await fetch(this.baseURL + 'getRoomsData', this.requsetInit)
            return response.json()
                .then(data => {
                    for (let i in data) {
                        let obj = {} as Rooms

                        obj.name = data[i][0]
                        obj.electrical_sensors_count = data[i][1]
                        obj.id = data[i][2]
                        result.push(obj)
                    }

                    return result
                })
        } catch {
            return [] as RoomsSet
        }
    }

    public async getRoomsElectricalSensorsData(id: number): Promise<RoomsElectricalSet> {
        let result = [] as RoomsElectricalSet

        try {
            const response = await fetch(this.baseURL + `getRoomsElectricalSensorsData?id=${id}`, this.requsetInit)
            return response.json()
                .then(data => {
                    for (let i in data) {
                        let obj = {} as RoomsElectrical
                        obj.name = data[i][1]
                        obj.state = data[i][3]
                        obj.value = data[i][4]
                        obj.description = data[i][7]
                        result.push(obj)
                    }
                    return result
                })
        } catch (error) {
            return [] as RoomsElectricalSet
        }
    }
}