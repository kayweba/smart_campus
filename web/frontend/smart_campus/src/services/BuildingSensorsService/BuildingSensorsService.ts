import { BuildingSensors, BuildingSensorsModel, BuildingSensorsSet } from "../../models/BuildingSensorsModel";
import { BuildingSensorsServiceInterface } from "./BuldingSensorsServiceInterface";


export class BuildingSensorsService implements BuildingSensorsServiceInterface {
    private requestInit = {
        method: 'GET',
        headers: { "Content-Type": "application/json" },
    }

    private baseURL: string = 'http://localhost:8000/'

    public async getBuildingSensorsData(buildingId: number): Promise<BuildingSensorsModel> {
        let result = [] as BuildingSensorsSet
        let resultRecord = {} as BuildingSensorsModel
        let buildingFloorKeySet = [] as Array<string>

        try {
            const response = await fetch(this.baseURL + `getBuildingSensorsData?building_id=${buildingId}`, this.requestInit)
            return response.json()
                .then(data => {
                    for (let i in data) {
                        let obj = {} as BuildingSensors

                        obj.electricalSensorId = data[i][0]
                        obj.roomDescription = data[i][1]
                        obj.roomNumber = data[i][2]
                        obj.electricalSensorName = data[i][3]
                        obj.electricalSensorTypeName = data[i][4]
                        obj.electricalSensorValue = data[i][5]
                        obj.electricalSensorState = data[i][6]

                        buildingFloorKeySet.push(data[i][2].toString()[0])

                        result.push(obj)
                    }

                    buildingFloorKeySet = buildingFloorKeySet.filter((element, index) => {
                        return buildingFloorKeySet.indexOf(element) === index
                    })

                    for (let index in buildingFloorKeySet) {
                        const filteredResiltArrayByRoomIndex = result.filter(element => {
                            return element.roomNumber.toString()[0] === buildingFloorKeySet[index]
                        })
                        resultRecord = {
                            ...resultRecord,
                            [buildingFloorKeySet[index]]: filteredResiltArrayByRoomIndex
                        }
                    }



                    return resultRecord
                })
        } catch {
            return {} as BuildingSensorsModel
        }

    }
}