

export interface GeneratorServiceInterface {

    /**
     * Останавливает генерацию случайных значений в БД.
     */
    stop(): void
    /**
     * @param interval частота обновления данных в БД.
     * Запускает на сервере генератор случайных чисел
     */
    start(interval: number): void
}