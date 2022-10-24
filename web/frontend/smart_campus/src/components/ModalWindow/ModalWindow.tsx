import { List, ListItem, Modal, Typography } from '@mui/material'
import { Box } from '@mui/system'
import React from 'react'
import { RoomsElectricalSet } from '../../models/SmartKampusModel'
import { Power, EmojiObjects, EmojiObjectsOutlined, PowerOutlined } from '@mui/icons-material';

import styles from './ModalWindow.module.css'

type ModalWindowProps = {
    onClose: () => void,
    modalOpen: boolean,
    data: RoomsElectricalSet,
    roomName: string
}


type ModalWindowState = {}

export class ModalWindow extends React.Component<ModalWindowProps, ModalWindowState> {

    public render(): React.ReactNode {

        const getItem = (descriprion: string, state: number = 1) => {
            switch (descriprion) {
                case 'Розетки':
                    return <div className={styles.header}>
                        {
                            state === 1
                                ? <Power style={{ color: '#0652FF' }} />
                                : <PowerOutlined />
                        }
                        <Typography style={{ marginTop: '2px', marginLeft: '2px' }}>
                            Розетки
                        </Typography>
                    </div>
                case 'Свет':
                    return <div className={styles.header}>
                        {
                            state === 1
                                ? <EmojiObjects style={{ color: '#FFCF48' }} />
                                : <EmojiObjectsOutlined />
                        }
                        <Typography style={{ marginTop: '2px', marginLeft: '2px' }}>
                            Свет
                        </Typography>
                    </div>
                default:
                    return descriprion
            }
        }

        return (
            <Modal
                open={this.props.modalOpen}
                onClose={this.props.onClose}
                aria-labelledby="modal-modal-title"
                aria-describedby="modal-modal-description"
            >
                <Box className={styles.modalWindowWrapper}>
                    <p style={{ color: '#686868', fontSize: '18px', fontWeight: 'bold' }}> {this.props.roomName} </p>
                    {
                        this.props.data.map(item =>
                            <Box key={item.name} sx={{ border: '1px solid #272727' }}>
                                <List>
                                    <ListItem>
                                        {getItem(item.description, item.state)}
                                    </ListItem>
                                    <Box marginLeft='20px'>
                                        <ListItem>
                                            <b>Описание: &nbsp;</b> {item.name}
                                        </ListItem>
                                        <ListItem>
                                            <b>Состояние: &nbsp;</b> {item.state}
                                        </ListItem>
                                        <ListItem>
                                            <b>Показатель (вольт): &nbsp;</b>
                                            <span>{item.value}</span>
                                        </ListItem>
                                    </Box>
                                </List>
                            </Box>
                        )
                    }
                </Box>
            </Modal>
        )
    }
}