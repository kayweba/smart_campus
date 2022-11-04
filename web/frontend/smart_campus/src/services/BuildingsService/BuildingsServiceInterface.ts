import { BuildingSet } from "../../models/BuildingModel"

export interface BuildingsServiceInterface {

    /**
     * @return JSON объект, содержащий список зданий
     */
    getBuildings(): Promise<BuildingSet>
}