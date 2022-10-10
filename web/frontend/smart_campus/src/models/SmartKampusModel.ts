
export type Rooms = {
    id: number,
    name: string,
    electrical_sensors_count: number,
}

export type RoomsElectrical = {
    name: string,
    state: 0 | 1,
    value: number,
    description: string
} 