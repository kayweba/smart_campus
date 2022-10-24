import React from 'react'
import { RoomsElectricalSet } from '../../models/SmartKampusModel'

const defaultValue = {
    roomsElectrical: [] as RoomsElectricalSet,
    setRoomsElectricalValue: (roomsElectrical: RoomsElectricalSet) => {}
}

const ReportContext = React.createContext(defaultValue)

type ReportProviderProps = {
    children: React.ReactNode
}

class ReportProvider extends React.Component<ReportProviderProps> {

    state = {
        roomsElectrical: [] as RoomsElectricalSet
    }

    setRoomsElectricalValue = (roomsElectrical: RoomsElectricalSet): void => {
        this.setState({
            ...this.state,
            roomsElectrical,
        })
    }


    public render(): React.ReactNode {
        const { children } = this.props
        const { roomsElectrical } = this.state
        const { setRoomsElectricalValue } = this


        return (
            <ReportContext.Provider value={{ roomsElectrical, setRoomsElectricalValue }}>
                { children }
            </ReportContext.Provider>
        )
    }

} 

export default ReportContext

export { ReportProvider }

