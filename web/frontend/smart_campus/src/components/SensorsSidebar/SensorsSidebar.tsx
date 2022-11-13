import { EmojiObjects, EmojiObjectsOutlined, Power, PowerOutlined, Waves } from "@mui/icons-material";
import { Box, Grid, Typography } from "@mui/material";
import React, { ReactNode } from "react";
import { BuildingSensorsModel } from "../../models/BuildingSensorsModel";
import { BuildingSensorsService } from "../../services/BuildingSensorsService/BuildingSensorsService";

import style from './SensorsSidebar.module.css'

type SensorsSidebarProps = {
    buildingId: number
}

type SensorsSidebarState = {
    buildingSensors: BuildingSensorsModel
}

export class SensorsSidebar extends React.Component<SensorsSidebarProps, SensorsSidebarState> {

    state = {
        buildingSensors: {} as BuildingSensorsModel
    }

    async componentDidUpdate(prevProps: Readonly<SensorsSidebarProps>, prevState: Readonly<{}>, snapshot?: any) {
        if (prevProps.buildingId !== this.props.buildingId) {
            this.updateData()
        } else {
            console.log('clearInterval');
            clearInterval(this.updateData())
        }        
    }

    updateData = () => setInterval(async () => {
        const buildingSensors = await new BuildingSensorsService().getBuildingSensorsData(this.props.buildingId)
        this.setState({
            ...this.state,
            buildingSensors: buildingSensors
        })
    }, 1500)

    componentWillUnmount() {
        console.log('componentWillUnmount');

        clearInterval(this.updateData())
    }

    private getItem(electricalSensorTypeName: string, state: number): ReactNode {
        switch (electricalSensorTypeName) {
            case 'Контроль розетки':
                return <div style={{ display: 'flex' }}>
                    {
                        state === 1
                            ? <Power className={style.power} />
                            : <PowerOutlined className={style.powerOutlined} />
                    }
                    <Typography style={{ marginTop: '2px', marginLeft: '2px' }}>
                        Розетки
                    </Typography>
                </div>
            case 'Контроль света':
                return <div style={{ display: 'flex' }}>
                    {
                        state === 1
                            ? <EmojiObjects className={style.emojiObjects} />
                            : <EmojiObjectsOutlined className={style.emojiObjectsOutlined} />
                    }
                    <Typography style={{ marginTop: '2px', marginLeft: '2px' }}>
                        Свет
                    </Typography>
                </div>
            case 'Контроль отопления':
                return <div style={{ display: 'flex' }}>
                    {
                        state === 1
                            ? <Waves style={{ color: '#F4CA00' }} className={style.waves} />
                            : <Waves className={style.wavesOff}/>
                    }
                    <Typography style={{ marginTop: '2px', marginLeft: '2px' }}>
                        Отопление
                    </Typography>
                </div>
            default:
                return electricalSensorTypeName
        }
    }

    public render(): React.ReactNode {
        return (
            <Grid container flexDirection='column'>
                {
                    Object.entries(this.state.buildingSensors).map(([key, buildingsSensor]) => (
                        <div key={key}>
                            <h3 key={buildingsSensor[0].electricalSensorValue} style={{ lineHeight: '0', textAlign: 'center' }}>Этаж: {key}</h3>
                            <Grid key={key} item className={style.sensorsSidebar}>
                                {
                                    buildingsSensor.map((buildingSensor, key) =>
                                        <Box key={key}>
                                            {this.getItem(buildingSensor.electricalSensorTypeName, buildingSensor.electricalSensorState)}
                                            <p><span style={{ fontWeight: 'bold' }}>Состояние</span>: {buildingSensor.electricalSensorState === 1 ? 'Вкл' : 'Выкл'}</p>
                                            <p><span style={{ fontWeight: 'bold' }}>Значение:</span> {buildingSensor.electricalSensorValue}</p>
                                            <p><span style={{ fontWeight: 'bold' }}>Описание:</span> {buildingSensor.electricalSensorName}</p>
                                            <p><span style={{ fontWeight: 'bold' }}>Номер комнаты:</span> {buildingSensor.roomNumber}</p>
                                        </Box>

                                    )
                                }

                            </Grid>
                        </div>
                    ))
                }
            </Grid>
        )
    }
}