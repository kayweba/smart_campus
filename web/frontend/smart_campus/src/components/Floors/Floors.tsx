import { Grid } from "@mui/material";
import React from "react";
import { FloorsModel } from "../../models/FloorModel";
import { FloorsService } from "../../services/FloorsService/FloorsService";
import { Floor } from "../Floor/Floor";
import schemeGif from '../../assets/sammy-lightning.gif'

type FloorsProps = {
    buildingId: number
}

type FloorsState = {
    floors: FloorsModel
}

export class Floors extends React.Component<FloorsProps, FloorsState> {

    state = {
        floors: {} as FloorsModel
    }

    async componentDidUpdate(prevProps: Readonly<FloorsProps>, prevState: Readonly<FloorsState>, snapshot?: any) {
        if (prevProps !== this.props) {
            const data = await new FloorsService().getFloorsDataByBuildingId(this.props.buildingId)
            this.setState({
                ...this.state,
                floors: data
            })
        }
    }

    public render(): React.ReactNode {
        return (
            <>


                <Grid container flexDirection={'column'}>
                    {
                        this.props.buildingId > 0
                        ?
                            Object.entries(this.state.floors).map(([key, value]) => (
                                <Floor rooms={value} floorNumber={key} key={key} />
                            ))
                        : <img src={schemeGif} alt="Схема " style={{ margin: '0 auto' }} />

                    }

                </Grid>

            </>
        )
    }
}