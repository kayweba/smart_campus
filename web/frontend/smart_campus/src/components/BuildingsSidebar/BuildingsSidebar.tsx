import { Button, CircularProgress, Grid } from "@mui/material";
import React from "react";
import { BuildingSet } from "../../models/BuildingModel";
import { BuildingsService } from "../../services/BuildingsService/BuildingsService";

import style from './BuildingsSidebar.module.css'

type BuildingsSidebarProps = {
    setBuildingId: (id: number) => void
}

type BuldingsSidebarState = {
    buildings: BuildingSet,
    isLoading: boolean
}

export class BuldingsSidebar extends React.Component<BuildingsSidebarProps, BuldingsSidebarState> {

    state = {
        buildings: [] as BuildingSet,
        isLoading: false
    }

    async componentDidMount() {
        this.setState({
            isLoading: true
        })
        const buildingsData = await new BuildingsService().getBuildings()
        this.setState({
            isLoading: false,
            buildings: buildingsData
        })
    }

    public render(): React.ReactNode {
        return (
            <Grid container flexDirection='column' alignItems='center'>
                {
                    this.state.isLoading
                        ? <CircularProgress size={20} color="success" className={style.circularProgress} />
                        : this.state.buildings.map((building, key) =>
                            <Button onClick={() => this.props.setBuildingId(building.id)} 
                                    key={key} 
                                    variant='contained' 
                                    size="small" 
                                    color='primary' 
                                    className={style.buildingBtn}
                            >
                                {building.description}
                            </Button>
                        )
                }

            </Grid>
        )
    }
}