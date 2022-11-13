import React from 'react'
import { Box, Button, Card, CardContent, Divider, Tooltip, Typography } from '@mui/material'

import { ModalWindow } from '../ModalWindow/ModalWindow'
import { ElectricalService } from '../../services/ElectricalService/ElectricalService'
import { RoomsElectrical } from '../../models/SmartKampusModel'

import styles from './Room.module.css'
import { StatusColorComponent } from '../StatusColor/StatusColorComponent'

type RoomComponentProps = {
    name: string,
    electricalSensorsCount: number,
    id: number,
    roomNumber: number,
    setErrorFlag: (flag: boolean) => void,
}

type RoomComponentState = {
    modalOpen: boolean,
    modalData: Array<RoomsElectrical>,
    statuses: Array<string>
}

export class RoomComponent extends React.Component<RoomComponentProps, RoomComponentState> {

    public render(): React.ReactNode {
        const { name, roomNumber, electricalSensorsCount } = this.props

        const handleClick = async () => {
            this.setState({
                modalOpen: true,
            })
        }
        const handleClose = () => {
            this.setState({
                modalOpen: false
            })
        }

        return (
            <>
                <Card className={styles.card_style}>
                    <CardContent sx={{ padding: '12px' }}>
                        <Tooltip title='Номер комнаты' placement='top' arrow>
                            <Typography variant='h6' component='div'>
                                {roomNumber}
                            </Typography>
                        </Tooltip>
                        <Divider />
                        <Typography sx={{ marginTop: '8px' }} component='div'>
                            Датчиков: {electricalSensorsCount}
                        </Typography>
                            <StatusColorComponent statuses={this.state.statuses}></StatusColorComponent>
                        <Box>
                            <Button size='small' variant='contained' sx={{ marginTop: '12px', fontSize: '11px' }} onClick={() => handleClick()}>Подробнее</Button>
                        </Box>
                    </CardContent>
                </Card>

                <ModalWindow roomName={name} modalOpen={this.state.modalOpen} onClose={handleClose} data={this.state.modalData} />

            </>
        )
    }

    state = {
        modalOpen: false,
        modalData: [],
        statuses: [] as Array<string>
    }

    componentDidMount() {
        this.updateData()
    }

    componentWillUnmount() {
        clearInterval(this.updateData())
    }

    updateData = () => setInterval(async () => {
        const data: Array<RoomsElectrical> = await new ElectricalService().getRoomsElectricalSensorsData(this.props.id)
        const statuses: Array<string> = []

        data.forEach(item => {
            if ((item.value < 200.5) || (item.value > 229.6)) {
                statuses.push('WARNING')
            } else {
                statuses.push('SUCCESS')
            }
        }
        )

        this.setState({
            ...this.state,
            modalData: data,
            statuses: statuses
        })

    }, 1500)

}