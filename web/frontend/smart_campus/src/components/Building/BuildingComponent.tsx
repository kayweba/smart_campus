import { Button, Card, CardActionArea, CardActions, CardContent, CircularProgress, Grid, Typography } from "@mui/material";
import { Box } from "@mui/system";
import React from "react";
import { BuildingsService } from "../../services/BuildingsService/BuildingsService";
import { Link } from 'react-router-dom'

type BuildingProps = {
    setBuildingId: (id: number) => void
}

type BuildingState = {
    isLoading: boolean,
    buildings: BuildingSet
}
type BuildingSet = Array<Building>

type Building = {
    id: number,
    building_number: number,
    description: string
}

export class BuildingComponent extends React.Component<BuildingProps, BuildingState> {

    state = {
        isLoading: false,
        buildings: [] as BuildingSet
    }

    async componentDidMount() {
        this.setState({
            isLoading: true
        })

        const data = await new BuildingsService().getBuildings()
        this.setState({
            isLoading: false,
            buildings: data
        })
    }

    private openBuild = (idBuild: number): void => {
        this.props.setBuildingId(idBuild)
        
    }

    public render(): React.ReactNode {
        return (
            this.state.isLoading
                ? <CircularProgress size={100} sx={{ top: '50%', left: '50%', position: 'absolute' }} color="success" />
                :
                <Grid container justifyContent='space-between' width='90%' margin='20px auto'>
                    {
                        this.state.buildings.map((building, key) =>
                            <Grid item key={key}>
                                <Card className="CardItem" sx={{ width: '300px', height: '300px', }} raised>
                                    <CardContent sx={{ display: 'flex', flexDirection: 'column', height: '100%' }}>
                                        <Box sx={{ height: '40%' }}>
                                            <span style={{ fontWeight: 'bold' }}>Наименование</span>
                                            <Typography gutterBottom variant='subtitle1' component="div">
                                                {building.description}
                                            </Typography>
                                        </Box>
                                        <Box sx={{ marginTop: '10px', height: '40%' }}>
                                            <Typography gutterBottom variant='subtitle1' component="div">
                                                <span style={{ fontWeight: 'bold' }}>Номер здания: </span> {building.building_number}
                                            </Typography>
                                        </Box>
                                        <CardActions>
                                            <Link to={`building${building.id}`} style={{ textDecoration: 'none' }}>
                                                <Button variant="outlined" color='success' onClick={() => this.openBuild(building.id)}>Перейти</Button>
                                            </Link>
                                        </CardActions>

                                    </CardContent>
                                </Card>
                            </Grid>
                        )
                    }

                </Grid>
        )
    }
}