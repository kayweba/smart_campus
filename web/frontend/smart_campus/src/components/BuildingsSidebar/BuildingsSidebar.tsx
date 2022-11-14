import { Button, CircularProgress, Grid } from "@mui/material";
import React from "react";
import { Building, BuildingSet } from "../../models/BuildingModel";
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
            <Grid container flexDirection='column'>
                {
                    this.state.isLoading
                        ? <CircularProgress size={20} color="success" className={style.circularProgress} />
                        : this.state.buildings.map((building, key) =>
                            this.getBuildingPlan(building, key)
                        )
                }

            </Grid>
        )
    }

    private getBuildingPlan(building: Building, key: number): React.ReactElement {
        switch (building.building_number) {
            case 1:
                return <button key={key} onClick={() => this.props.setBuildingId(building.building_number)} className={style.korpus_btn}>
                    <div>
                        <span style={{ position: 'relative', top: '48px', color: '#fff' }}>Корпус {building.building_number}</span>
                        <svg width="129" height="64" viewBox="0 0 129 64" fill="none" xmlns="http://www.w3.org/2000/svg">
                            <path className={style.svg} d="M0 64V0H23.5H45.2396V22.0819H89.1354V0H129V64H0Z" fill="#3D3D3D" />
                        </svg>

                    </div>
                </button>
            case 2:
                return <button key={key} onClick={() => this.props.setBuildingId(building.building_number)} className={style.korpus_btn}>
                    <div>
                        <span style={{ position: 'relative', top: '45px', color: '#fff' }}>Корпус {building.building_number}</span>
                        <svg width="144" height="68" viewBox="0 0 144 68" fill="none" xmlns="http://www.w3.org/2000/svg">
                            <path className={style.svg} d="M0 63.2051V10.8974H9.40703V0H30.392V10.8974H112.161V0H132.784V8.71795H144V63.2051H112.161V68H95.1558V63.2051H0Z" fill="#3D3D3D" />
                        </svg>
                    </div>
                </button>
            case 3:
                return <button key={key} onClick={() => this.props.setBuildingId(building.building_number)} className={style.korpus_btn}>
                    <div>
                        <span style={{ position: 'relative', top: '31px', color: '#fff' }}>Корпус {building.building_number}</span>
                        <svg width="144" height="50" viewBox="0 0 144 50" fill="none" xmlns="http://www.w3.org/2000/svg">
                            <path className={style.svg} d="M0 50V3.14961V0H136.624V3.14961H144V44.8819H136.624V50H0Z" fill="#3D3D3D" />
                        </svg>
                    </div>
                </button>
            case 4:
                return <button key={key} onClick={() => this.props.setBuildingId(building.building_number)} className={style.korpus_btn}>
                    <div>
                        <span style={{ position: 'relative', top: '37px', color: '#fff' }}>Корпус {building.building_number}</span>
                        <svg width="148" height="60" viewBox="0 0 148 60" fill="none" xmlns="http://www.w3.org/2000/svg">
                            <path className={style.svg} d="M0 51.2308V3.69231V2.30769H15.1364V9.46154H93.9949V5.53846H103.152V8.30769H132.303V0H148V51.2308H51.0152V60H30.2727V51.2308H0Z" fill="#3D3D3D" />
                        </svg>
                    </div>
                </button>
            case 5:
                return <button key={key} onClick={() => this.props.setBuildingId(building.building_number)} className={style.korpus_btn}>
                    <div>
                        <span style={{ position: 'relative', top: '38px', color: '#fff' }}>Корпус {building.building_number}</span>
                        <svg width="153" height="63" viewBox="0 0 153 63" fill="none" xmlns="http://www.w3.org/2000/svg">
                            <path className={style.svg} d="M153 63H0V8.06707V5.37805V0H153V63Z" fill="#3D3D3D" />
                        </svg>

                    </div>
                </button>
            default:
                return <Button key={key} onClick={() => this.props.setBuildingId(building.building_number)}
                    variant='contained'
                    size="small"
                    color='primary'
                    className={style.buildingBtn}
                >
                    {building.description}
                </Button>
        }
    }
}