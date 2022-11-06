import { OtherHousesOutlined } from "@mui/icons-material";
import { Grid, IconButton } from "@mui/material";
import React from "react";
import { RoomsSet } from "../../models/SmartKampusModel";
import { RoomComponent } from "../Room/RoomComponent";
import { RoomsComponent } from "../Rooms/RoomsComponent";

type FloorProps = {
    rooms: RoomsSet,
    floorNumber: string
}

export class Floor extends React.Component<FloorProps> {
    public render(): React.ReactNode {
        return (
            <>
                <Grid alignItems={'space-between'} sx={{ marginTop: '20px' }}>
                    <h1 style={{ textAlign: 'center' }}>Этаж: {this.props.floorNumber}</h1>
                    <Grid item justifyContent={'space-between'} alignItems={'center'} margin={'10px auto 10px'} sx={{ border: '2px solid #fff' }}>
                        <RoomsComponent rooms={this.props.rooms} />
                    </Grid>
                </Grid>

            </>
        )
    }
}