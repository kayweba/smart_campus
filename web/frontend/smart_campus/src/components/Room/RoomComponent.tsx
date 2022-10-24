import React from 'react'
import { Box, Button, Card, CardContent, Divider, Typography } from '@mui/material'

import { ModalWindow } from '../ModalWindow/ModalWindow'
import { ElectricalService } from '../../services/ElectricalService/ElectricalService'
import { RoomsElectrical } from '../../models/SmartKampusModel'
import { StatusColorComponent } from '../StatusColor/StatusColorComponent'

import styles from './Room.module.css'
import ReportContext from '../ReportProvider/ReportProvider'

type RoomComponentProps = {
    name: string,
    electricalSensorsCount: number,
    id: number,
    setErrorFlag: (flag: boolean) => void
}

type RoomComponentState = {
    modalOpen: boolean,
    modalData: Array<RoomsElectrical>,
    status: string
}


export class RoomComponent extends React.Component<RoomComponentProps, RoomComponentState> {
    // Typescript может определить тип конкеста таким образом
    static contextType = ReportContext
    context!: React.ContextType<typeof ReportContext>

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

        const { setRoomsElectricalValue } = this.context

        if (data.length === 0) {
            this.props.setErrorFlag(true)
        } else {
            let status = ''
            this.props.setErrorFlag(false)

            data.forEach(item => {
                if (item.value < 210 || item.value > 220) {
                    status = 'WARNING'
                    setRoomsElectricalValue(data)
                } else {
                    status = 'SUCCESS'
                }
            }
            )

            this.setState({
                modalData: data,
                status: status
            })
        }

    }, 2000)

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
                <Card className={styles.card_style}>
                    <CardContent>
                        <Typography variant='h6' component='div'>
                            {name}
                        </Typography>
                        <Divider />
                        <Typography sx={{ marginTop: '16px' }} component='div'>
                            Количество датчиков в комнате: {electricalSensorsCount}
                        </Typography>
                        <div style={{ marginTop: '6px' }}>
                            Статус: <span><StatusColorComponent type={this.state.status} style={{ position: 'absolute', marginTop: '7px', marginLeft: '10px' }} /></span>
                        </div>
                        <Box>
                            <Button size='small' variant='contained' sx={{ marginTop: '24px' }} onClick={() => handleClick()}>Подробнее</Button>
                        </Box>
                    </CardContent>
                </Card>

                <ModalWindow roomName={name} modalOpen={this.state.modalOpen} onClose={handleClose} data={this.state.modalData} />

            </>
        )
    }
}