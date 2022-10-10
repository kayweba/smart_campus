import React from 'react'
import { Box, Button, Card, CardContent, Divider, Typography } from '@mui/material'

import './Room.css'
import { ModalWindow } from '../ModalWindow/ModalWindow'
import { ElectricalService } from '../../services/ElectricalService/ElectricalService'
import { RoomsElectrical } from '../../models/SmartKampusModel'
import { StatusColorComponent } from '../StatusColor/StatusColorComponent'

type RoomComponentProps = {
    name: string,
    electricalSensorsCount: number,
    id: number
}

type RoomComponentState = {
    modalOpen: boolean,
    modalData: Array<RoomsElectrical>,
    status: string
}


export class RoomComponent extends React.Component<RoomComponentProps, RoomComponentState> {

    state = {
        modalOpen: false,
        modalData: [],
        status: ''
    }

    componentDidMount() {
        this.updateData()
    }

    updateData = () => setInterval(async () => {
        const data: Array<RoomsElectrical> = await new ElectricalService().getRoomsElectricalSensorsData(this.props.id)
        let status = ''

        data.forEach(item => {
                if (item.value < 210 || item.value > 220) {
                    status = 'WARNING'
                } else {
                    status = 'SUCCESS'
                }
            }
        )

        this.setState({
            modalData: data,
            status: status
        })

    }, 1500)

    public render(): React.ReactNode {
        const { name, electricalSensorsCount } = this.props

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
                <Card className='card_style'>
                    <CardContent>
                        <Typography variant='h5' component='div'>
                            {name}
                        </Typography>
                        <Divider />
                        <Typography style={{ marginTop: '16px' }} className={'sensors_amount'} component='div'>
                            Количество датчиков в комнате: {electricalSensorsCount}
                        </Typography>
                        <div>
                        Статус: <span><StatusColorComponent type={this.state.status} style={{ position: 'fixed', marginTop: '6px', marginLeft: '10px' }} /></span>
                        </div> 
                        <Box>
                            <Button variant='contained' sx={{ marginTop: '24px' }} onClick={() => handleClick()}>Подробнее</Button>
                        </Box>
                    </CardContent>
                </Card>

                <ModalWindow roomName={name} modalOpen={this.state.modalOpen} onClose={handleClose} data={this.state.modalData} />
            </>
        )
    }
}