import React from 'react'
import { ErrorOutlineOutlined } from '@mui/icons-material';
import { Grid } from '@mui/material'
import { RoomsSet } from '../../models/SmartKampusModel'
import { RoomComponent } from '../Room/RoomComponent'

import styles from './Rooms.module.css'

type RoomsComponentProps = {
    rooms: RoomsSet
}

type RoomsComponentState = {
    error: boolean,
}
export class RoomsComponent extends React.Component<RoomsComponentProps, RoomsComponentState> {
    state = {
        error: false,
    }

    public render(): React.ReactNode {

        const setErrorFlag = (flag: boolean): void => {
            this.setState({
                ...this.state,
                error: flag
            })
        }

        return (

            <>
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
                                    <RoomComponent
                                        setErrorFlag={setErrorFlag}
                                        name={item.name}
                                        electricalSensorsCount={item.electrical_sensors_count}
                                        id={item.id}
                                        roomNumber={item.room_number}
                                    />
                                </Grid>
                            )
                    }
                </Grid>
            </>
        )
    }
}