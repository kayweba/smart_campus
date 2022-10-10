import { Grid } from '@mui/material'
import React, { CSSProperties } from 'react'
import { Rooms } from '../../models/SmartKampusModel'
import { ElectricalService } from '../../services/ElectricalService/ElectricalService'

import { RoomComponent } from '../Room/RoomComponent'

type RoomsComponentProps = {}

type RoomsComponentState = {
    smartKampus: Array<Rooms>
}

export class RoomsComponent extends React.Component<RoomsComponentProps, RoomsComponentState> {

    state = {
        smartKampus: [] as Array<Rooms>
    }

    async componentDidMount() {
        const data = await new ElectricalService().getRooms()
        this.setState({
            smartKampus: data
        })
    }

    public render(): React.ReactNode {

        const gridContainerStyle = {
            maxWidth: '1600px',
            margin: '20px auto'
        } as CSSProperties

        return (
            <Grid container sx={gridContainerStyle} direction="row" spacing={1}>
                {
                    this.state.smartKampus.map(item =>
                        <Grid key={item.name} item>
                            <RoomComponent name={item.name} electricalSensorsCount={item.electrical_sensors_count} id={item.id} />
                        </Grid>
                    )
                }
            </Grid>
        )
    }
}