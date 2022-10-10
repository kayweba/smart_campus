import { Rooms, RoomsElectrical } from "../../models/SmartKampusModel";


export interface ElectricalServiceInterface {
    /**
     * @return JSON объект, содержащий общую информацию о комнатах (назавание, количество датчиков, id комнаты)
     */
    getRooms(): Promise<Array<Rooms>>
    /**
     * @param id - id комнаты, по которой необходимо получить данные
     * @return объект, который содержит подробную информацию о конкретной комнате (тип датчика, его расположение в комнате, состояние, значение)
     */
    getRoomsElectricalSensorsData(id: number): Promise<Array<RoomsElectrical>>
}