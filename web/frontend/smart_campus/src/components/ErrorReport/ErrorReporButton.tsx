import { Badge, Button, Grid } from "@mui/material"
import React from "react"

type ErrorReportButtonProps = {
    onClick: () => void,
    numberErrors: number
}

export class ErrorReportButton extends React.Component<ErrorReportButtonProps> {

    public render(): React.ReactNode {
        return (
            <Grid container justifyContent='center' margin='20px 0 10px 0'>
                <Badge badgeContent={this.props.numberErrors} color='error'>
                    <Button variant='outlined' color='error'>Отчет об ошибках</Button>
                </Badge>
            </Grid>
        )
    }
}