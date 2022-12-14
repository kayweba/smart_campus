
export type RoomsSet = Array<Rooms>
export type RoomsElectricalSet = Array<RoomsElectrical>

export type Rooms = {
    id: number,
    name: string,
    electrical_sensors_count: number,
    room_number: number,
}

export type RoomsElectrical = {
    name: string,
    state: 0 | 1,
    value: number,
    description: string
} 