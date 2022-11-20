import { GeneratorServiceInterface } from "./GeneratorServiceInterface";

export class GeneratorService implements GeneratorServiceInterface {

    private requsetInit = {
        method: 'GET',
        headers: { "Content-Type": "application/json" },
    }

    private baseURL: string = 'http://localhost:8000/'
    
    public async start(interval: number) {
        try {
            await fetch(this.baseURL + `startGenerator?interval=${interval}`, this.requsetInit)
            return
        } catch(error) {
            throw new Error('Ошибка старта генератора')
        }
    }

    public async stop() {
        try {
            await fetch(this.baseURL + `stopGenerator`, this.requsetInit)
            return
        } catch(error) {
            console.error('Ошибка при попытке остановить генератор', error)
        }
    }
}