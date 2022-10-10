import { Divider, List, ListItem, Modal, Typography } from '@mui/material'
import { Box } from '@mui/system'
import React, { CSSProperties } from 'react'
import { RoomsElectrical } from '../../models/SmartKampusModel'
import { Power, EmojiObjects, EmojiObjectsOutlined, PowerOutlined } from '@mui/icons-material';

type ModalWindowProps = {
    onClose: () => void,
    modalOpen: boolean,
    data: Array<RoomsElectrical>,
    roomName: string
}


type ModalWindowState = {}

export class ModalWindow extends React.Component<ModalWindowProps, ModalWindowState> {

    public render(): React.ReactNode {
        // TODO: Перенести стили в отдельные файлы
        const style = {
            position: 'absolute' as 'absolute',
            top: '50%',
            left: '50%',
            transform: 'translate(-50%, -50%)',
            minWidth: 400,
            bgcolor: 'background.paper',
            border: '2px solid #000',
            boxShadow: 24,
            p: 4,
        };

        const heaaderStyle = {
            display: 'flex',
            alignItems: 'center',
            justifyContent: 'center',
        } as CSSProperties

        const getItem = (descriprion: string, state: number = 1) => {
            switch (descriprion) {
                case 'Розетки':
                    return <div style={heaaderStyle}>
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
                    return <div style={heaaderStyle}>
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
                <Box sx={style}>
                    <h2 style={{ color: '#686868' }}> {this.props.roomName} </h2>
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
                                {/* <Divider /> */}
                            </Box>
                        )
                    }
                </Box>
            </Modal>
        )
    }
}