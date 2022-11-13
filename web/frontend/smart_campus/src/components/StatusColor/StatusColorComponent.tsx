import { Box } from '@mui/system'
import React, { CSSProperties } from 'react'

import style from './StatusColorComponent.module.css'

type StatusColorComponentProps = {
    statuses: Array<string>,
    style?: CSSProperties,
}

export class StatusColorComponent extends React.Component<StatusColorComponentProps> {
    public render(): React.ReactNode {
        return (
            <Box sx={{ display: 'flex', flexDirection: 'row', marginTop: '8px', marginBottom: '2px' }}>
                {this.props.statuses.map((status, key) =>
                    status === 'WARNING'
                        ? <div key={key} className={style.errorStatus} />
                        : <div key={key} className={style.normalStatus} />
                )}
            </Box>
        )
    }
}