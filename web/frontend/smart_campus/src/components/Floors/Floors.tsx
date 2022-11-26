import { Grid } from "@mui/material";
import React from "react";
import { FloorsModel } from "../../models/FloorModel";
import { FloorsService } from "../../services/FloorsService/FloorsService";
import { Floor } from "../Floor/Floor";


type FloorsProps = {
    buildingId: number,
    updateInterval: number,
    generatorIsActive: boolean,
}

type FloorsState = {
    floors: FloorsModel
}

export class Floors extends React.Component<FloorsProps, FloorsState> {

    state = {
        floors: {} as FloorsModel
    }

    public render(): React.ReactNode {
        return (
            <>
                <Grid container flexDirection={'column'}>
                    {
                        Object.entries(this.state.floors).map(([key, value]) => (
                            <Floor buildingId={this.props.buildingId} rooms={value} floorNumber={key} key={key} updateInterval={this.props.updateInterval} generatorIsActive={this.props.generatorIsActive} />
                        ))
                    }
                </Grid>

            </>
        )
    }

    async componentDidMount() {
        const data = await new FloorsService().getFloorsDataByBuildingId(this.props.buildingId)
        this.setState({
            ...this.state,
            floors: data
        })
    }

    async componentDidUpdate(prevProps: Readonly<FloorsProps>) {
        if (prevProps.buildingId !== this.props.buildingId) {
            const data = await new FloorsService().getFloorsDataByBuildingId(this.props.buildingId)
            this.setState({
                ...this.state,
                floors: data
            })
        }
    }
}