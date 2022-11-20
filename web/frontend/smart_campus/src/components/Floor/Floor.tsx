import { Grid } from "@mui/material";
import React from "react";
import { RoomsSet } from "../../models/SmartKampusModel";
import { RoomsComponent } from "../Rooms/RoomsComponent";

import style from './Floor.module.css'

type FloorProps = {
    rooms: RoomsSet,
    floorNumber: string,
    updateInterval: number,
    generatorIsActive: boolean,
    buildingId: number,
}

export class Floor extends React.Component<FloorProps> {
    public render(): React.ReactNode {
        return (
            <>
                <Grid alignItems={'space-between'} sx={{ marginTop: '20px' }}>
                    <h1 style={{ textAlign: 'center', fontSize: '16px', lineHeight: '8px' }}>Этаж: {this.props.floorNumber}</h1>
                    <Grid item justifyContent={'space-between'} alignItems={'center'} margin={'10px auto 10px'}className={style.floor}>
                        <RoomsComponent buildingId={this.props.buildingId} rooms={this.props.rooms} updateInterval={this.props.updateInterval} generatorIsActive={this.props.generatorIsActive} />
                    </Grid>
                </Grid>

            </>
        )
    }
}