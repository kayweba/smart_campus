import React from 'react'
import { RoomsElectricalSet } from '../../models/SmartKampusModel'


const defaultValue = [] as RoomsElectricalSet

const ReportContext = React.createContext(defaultValue)

export const ReportProvider = ReportContext.Provider
export const ReportConsumer = ReportContext.Consumer

export default ReportContext
