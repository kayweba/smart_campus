import { BuildingSensorsModel, BuildingSensorsSet } from "../../models/BuildingSensorsModel";


export interface BuildingSensorsServiceInterface {

    /**
     * @param id Id здания
     * @return список всех датчиков, которые находится внутри указанного здания
     */
    getBuildingSensorsData(buildingId: number): Promise<BuildingSensorsModel>
}