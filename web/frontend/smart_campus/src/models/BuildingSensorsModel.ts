
export type BuildingSensorsSet = Array<BuildingSensors>


export type BuildingSensors = {
    roomDescription: string,
    roomNumber: number,
    electricalSensorName: string,
    electricalSensorValue: number,
    electricalSensorState: number
    electricalSensorId: number,
    electricalSensorTypeName: string,
}

export type BuildingSensorsModel = Record<string, BuildingSensorsSet>