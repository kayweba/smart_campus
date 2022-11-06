import { FloorsModel } from "../../models/FloorModel";
import { RoomsSet } from "../../models/SmartKampusModel";


export interface FloorsServiceInterface {
    /**
     * @return JSON объект, содержащий информацию об помещениях на этажаж (кол-во датчиков, название комнат)
     * @param buildingId ID Здания для которого необходимо найти список этажей
     */
     getFloorsDataByBuildingId(buildingId: number): Promise<FloorsModel>
}
