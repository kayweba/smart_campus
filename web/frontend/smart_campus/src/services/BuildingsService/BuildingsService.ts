import { BuildingSet, Building } from "../../models/BuildingModel";
import { BuildingsServiceInterface } from "./BuildingsServiceInterface";



export class BuildingsService implements BuildingsServiceInterface {
    private requsetInit = {
        method: 'GET',
        headers: { "Content-Type": "application/json" },
    }
    private baseURL: string = 'http://localhost:8000/'

    public async getBuildings(): Promise<BuildingSet> {
        let result = [] as BuildingSet
        try {
            const response = await fetch(this.baseURL + 'getBuildingsData', this.requsetInit)
            return response.json()
                .then(data => {
                    for (let i in data) {
                        let obj = {} as Building
                        obj.id = data[i][0]
                        obj.building_number = data[i][1]
                        obj.description = data[i][2]
                        obj.cout_of_floors = data[i][3]
                        result.push(obj)
                    }
                    return result
                })
        } catch {
            return [] as BuildingSet
        } 
    }
}