import { Box, Button } from "@mui/material";
import React from "react";
import { ErrorReportModalWindow } from "./ErrorReportModalWindow/ErrorReportModalWindow";

type ErrorReportState = {
    showErrorReport: boolean
}

export class ErrorReport extends React.Component<{}, ErrorReportState> {

    state = {
        showErrorReport: false
    }

    public render(): React.ReactNode {

        const showErrorReport = (): void => {
            this.setState({
                ...this.state,
                showErrorReport: !this.state.showErrorReport
            })
        }

        return (
            <div style={{ width: '100%', height: '100%' }}>
                <Box sx={{ textAlign: 'center', marginTop: '12px' }}>
                    <Button variant='outlined' size='small' color='error' onClick={showErrorReport}>Отчет об ошибках</Button>
                </Box>
                {
                    this.state.showErrorReport 
                    ? <ErrorReportModalWindow onClose={showErrorReport}/>
                    : null
                }
            </div>
        )
    }

}