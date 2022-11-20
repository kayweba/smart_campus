import { PlayCircle, StopCircle } from '@mui/icons-material'
import { Grid, IconButton, TextField, Tooltip } from '@mui/material'
import React from 'react'
import { GeneratorService } from '../../services/GeneratorService/GeneratorService'

type GeneratorSettingsProps = {
    setGeneratorMode: (generatorIsActive: boolean) => void,
    setGeneratorInterval: (interval: number) => void,
}

type GeneratorSettingsState = {
    isStarted: boolean,
    interval: number
}

export class GeneratorSettings extends React.Component<GeneratorSettingsProps, GeneratorSettingsState> {

    state = {
        isStarted: false,
        interval: 1000,
    }

    public render(): React.ReactNode {
        return (
            <Grid container paddingTop={2} alignItems='center' justifyContent='center' position='absolute'>
                <Grid item sx={{ marginRight: '20px' }}>
                    {
                        this.state.isStarted === true
                            ? <Tooltip title='Остановить генератор'>
                                <IconButton onClick={() => this.stop()}>
                                    <StopCircle color='warning' />
                                </IconButton>
                              </Tooltip>
                            : <Tooltip title='Запустить генератор'>
                                <IconButton onClick={() => this.start()}>
                                    <PlayCircle color='primary' />
                                </IconButton>
                              </Tooltip>
                    }
                </Grid>
                <Grid item>
                    <TextField
                        disabled={this.state.isStarted} 
                        onChange={(event) => this.intervaleChange(parseInt(event.target.value))} 
                        sx={{ width: '200px' }} 
                        size='small' 
                        type='number' 
                        label='Частота обновления БД (мс)' 
                        inputProps={{ min: 500, max: 10000 }} 
                        defaultValue={1000} />
                </Grid>
            </Grid>
        )
    }

    private start = async () => {
        this.props.setGeneratorMode(true)
        this.props.setGeneratorInterval(this.state.interval)
        this.setState({
            ...this.state,
            isStarted: true
        })
        await new GeneratorService().start(this.state.interval)
    }

    private stop = async () => {
        this.props.setGeneratorMode(false)
        this.setState({
            ...this.state,
            isStarted: false
        })
        await new GeneratorService().stop()
    }

    private intervaleChange = (interval: number): void => {
        this.setState({
            ...this.state,
            interval
        })
    }

}