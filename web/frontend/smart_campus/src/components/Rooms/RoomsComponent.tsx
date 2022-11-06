import React, { Fragment } from 'react'

import { ErrorOutlineOutlined, OtherHousesOutlined } from '@mui/icons-material';
import { Grid, IconButton } from '@mui/material'

import { RoomsSet } from '../../models/SmartKampusModel'
import { ElectricalService } from '../../services/ElectricalService/ElectricalService'
import { RoomComponent } from '../Room/RoomComponent'

import styles from './Rooms.module.css'
import { ErrorReportButton } from '../ErrorReport/ErrorReporButton';
import { Link } from 'react-router-dom'
import { Floors } from '../Floors/Floors';

type RoomsComponentProps = {
    rooms: RoomsSet
}

type RoomsComponentState = {
    smartKampus: RoomsSet,
    error: boolean,
    numberErrors: number,
}
export class RoomsComponent extends React.Component<RoomsComponentProps, RoomsComponentState> {
    state = {
        smartKampus: [] as RoomsSet,
        error: false,
        numberErrors: 0,
    }

    public render(): React.ReactNode {

        const updateErrorsNumber = (): void => {
            this.setState({
                ...this.state,
                numberErrors: this.state.numberErrors + 1
            })
        }

        const setErrorFlag = (flag: boolean): void => {
            this.setState({
                ...this.state,
                error: flag
            })
        }

        return (

            <Fragment>
                <Grid container sx={{ margin: '0 auto' }} className={styles.gridContainer} direction="row" spacing={1}>
                    {
                        this.state.error
                            ?
                            <div>
                                <h3>ОШИБКА СОЕДИНЕНИЯ С СЕРВЕРОМ</h3>
                                <div style={{ position: 'fixed', left: '0', top: '0', display: 'flex', alignItems: 'center', justifyContent: 'center', width: '100vw', height: '100vh' }}>
                                    <div>
                                        <ErrorOutlineOutlined sx={{ fontSize: '120px', color: '#FF0000', opacity: '.3' }} />
                                    </div>
                                </div>
                            </div>
                            : this.props.rooms.map(item =>
                                <Grid key={item.name} item sx={{ marginBottom: '10px' }}>
                                    <RoomComponent setErrorFlag={setErrorFlag} name={item.name} electricalSensorsCount={item.electrical_sensors_count} id={item.id} updateErrorsNumber={updateErrorsNumber} />
                                </Grid>

                            )
                    }
                </Grid>
            </Fragment>
        )
    }
}