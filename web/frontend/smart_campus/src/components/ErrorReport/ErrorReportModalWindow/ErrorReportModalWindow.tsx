import { Close } from "@mui/icons-material";
import { Button, IconButton, Modal } from "@mui/material";
import { Box } from "@mui/system";
import React from "react";
import { RoomsElectricalSet } from "../../../models/SmartKampusModel";
import { ModalWindow } from "../../ModalWindow/ModalWindow";
import ReportContext from "../../ReportProvider/ReportProvider";

type ErrorReportModalWindowProps = {
    onClose: () => void,
}

type ErrorReportModalWindowState = {
    isShowErrorInfo: boolean
}

export class ErrorReportModalWindow extends React.Component<ErrorReportModalWindowProps, ErrorReportModalWindowState> {
    // Typescript может определить тип конкеста таким образом
    static contextType = ReportContext
    context!: React.ContextType<typeof ReportContext>

    state = {
        isShowErrorInfo: false
    }

    public render(): React.ReactNode {
        const showErrorInfo = (): void => {
            this.setState({
                ...this.state,
                isShowErrorInfo: !this.state.isShowErrorInfo
            })
        }

        const mockData = [{
            name: 'Розетка у кафедры',
            state: 0,
            value: 120.00,
            description: 'Розетки'
        }] as RoomsElectricalSet

        const { roomsElectrical } = this.context

        return (
            <>
                {
                    this.context.roomsElectrical
                        ?
                        <Modal open={true}>
                            <div style={{ margin: '7% auto', width: '60%', height: '70vh', backgroundColor: '#212121', padding: '8px 24px', borderRadius: '3px', overflow: 'auto' }} >
                                <Box sx={{ textAlign: 'right' }}>
                                    <IconButton aria-label="delete" size="small" sx={{ margin: '10px' }} onClick={this.props.onClose}>
                                        <Close fontSize="small" />
                                    </IconButton>
                                </Box>
                                <Box sx={{ display: 'flex', backgroundColor: '#0F0F0F', paddingLeft: '16px', borderRadius: '3px', justifyContent: 'space-between', alignItems: 'center', marginBottom: '8px' }}>
                                    <Box sx={{ display: 'flex' }}>
                                        <p style={{ marginRight: '16px' }}>24.10.2022</p>
                                        <p>Лаборатория №113</p>
                                    </Box>
                                    <Box sx={{ marginRight: '16px' }}>
                                        <Button size='small' variant='contained' onClick={showErrorInfo}>
                                            Подробнее
                                        </Button>
                                    </Box>
                                </Box>
                            </div>
                        </Modal>
                        : null
                }

                {
                    this.state.isShowErrorInfo
                        ? <ModalWindow modalOpen={this.state.isShowErrorInfo} onClose={showErrorInfo} data={roomsElectrical} roomName={'Лаборатория №113'} />
                        : null
                }

            </>
        )
    }
}