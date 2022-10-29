import { Box } from '@mui/system'
import React, { CSSProperties } from 'react'

type StatusColorComponentProps = {
    type: string
    style?: CSSProperties,
}

export class StatusColorComponent extends React.Component<StatusColorComponentProps> {

    // TODO: Переместить стили теней в переменные. Сейчас они в файле App.css
    private normalStatusStyle = {
        width: '10px',
        height: '10px',
        borderRadius: '50%',
        backgroundColor: '#66BB6A',
        ...this.props.style
    } as CSSProperties

    private errorStatusStyle = {
        width: '10px',
        height: '10px',
        borderRadius: '50%',
        backgroundColor: '#D32F2F',
        ...this.props.style
    } as CSSProperties


    private getStatusColor(type: string): React.ReactNode {
        switch (type) {
            case 'WARNING':
                return <Box component="span" sx={this.errorStatusStyle} />
            case 'SUCCESS':
                return <Box component="span" sx={this.normalStatusStyle} />
            default:
                break;
        }
    }


    public render(): React.ReactNode {
        return (
            this.getStatusColor(this.props.type)
        )
    }
}