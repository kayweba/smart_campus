import { Link } from "react-router-dom";
import { OtherHousesOutlined } from "@mui/icons-material";
import { Grid, IconButton } from "@mui/material";
import React from "react";
import { FloorsModel } from "../../models/FloorModel";
import { FloorsService } from "../../services/FloorsService/FloorsService";
import { Floor } from "../Floor/Floor";

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

    async componentDidMount() {
        const data = await new FloorsService().getFloorsDataByBuildingId(this.props.buildingId)
        this.setState({
            ...this.state,
            floors: data
        })
        console.log(data);
    }

    public render(): React.ReactNode {
        return (
            <>
                <Link to="/">
                    <IconButton sx={{ marginLeft: '20px', position: 'fixed' }}>
                        <OtherHousesOutlined color='success' />
                    </IconButton>
                </Link>
                <Grid container flexDirection={'column'}>
                    {
                        Object.entries(this.state.floors).map(([key, value]) => (
                            <Floor rooms={value} floorNumber={key} />
                        ))
                    }
                </Grid>
            </>
        )
    }
}