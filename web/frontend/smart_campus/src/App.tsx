import React from 'react';

import { ThemeProvider, createTheme } from '@mui/material/styles';

import './App.css';
import CssBaseline from '@mui/material/CssBaseline';
import { Floors } from './components/Floors/Floors';
import { BuldingsSidebar } from './components/BuildingsSidebar/BuildingsSidebar';
import { SensorsSidebar } from './components/SensorsSidebar/SensorsSidebar';
import { Grid } from '@mui/material';
import { GeneratorSettings } from './components/GeneratorSettings/GeneratorSettings';

import schemeGif from './assets/sammy-lightning.gif'

const darkTheme = createTheme({
  palette: {
    mode: 'dark',
  },
});

type AppState = {
  selectedBuildingId: number,
  interval: number,
  generatorIsActive: boolean,
}
class App extends React.Component<{}, AppState> {

  state = {
    selectedBuildingId: 0,
    interval: 1000,
    generatorIsActive: false,
  }

  public render(): React.ReactNode {

    const setBuildingId = (id: number) => {
      this.setState({
        selectedBuildingId: id
      })
    }

    const setGeneratorInterval = (interval: number) => {
      this.setState({
        interval: interval
      })
    }

    const setGeneratorMode = (generatorIsActive: boolean) => {
      this.setState({
        generatorIsActive: generatorIsActive
      })
    }

    return (
      <ThemeProvider theme={darkTheme}>
        <CssBaseline />
        <GeneratorSettings setGeneratorInterval={setGeneratorInterval} setGeneratorMode={setGeneratorMode} />
        <Grid container justifyContent='space-between' width='98%' margin='auto' height='100vh' alignItems='center'>
          <Grid width='8%' item>
            <BuldingsSidebar setBuildingId={setBuildingId} />
          </Grid>
          {
            this.state.selectedBuildingId > 0
              ? <>
                <Grid item width='76%' maxHeight='90vh' overflow='auto' paddingRight='15px'>
                  <Floors buildingId={this.state.selectedBuildingId} updateInterval={this.state.interval} generatorIsActive={this.state.generatorIsActive} />
                </Grid>
                <Grid item width='12%' maxHeight='90vh' overflow='auto' paddingRight='15px'>
                  <SensorsSidebar buildingId={this.state.selectedBuildingId} updateInterval={this.state.interval} generatorIsActive={this.state.generatorIsActive} />
                </Grid>
              </>
              : <img src={schemeGif} alt="Схема " style={{ margin: '0 auto' }} />
          }

        </Grid>
      </ThemeProvider>
    );
  }
}

export default App;
