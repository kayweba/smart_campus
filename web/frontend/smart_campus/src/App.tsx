import React from 'react';

import { ThemeProvider, createTheme } from '@mui/material/styles';

import './App.css';
import CssBaseline from '@mui/material/CssBaseline';
import { Floors } from './components/Floors/Floors';
import { BuldingsSidebar } from './components/BuildingsSidebar/BuildingsSidebar';
import { SensorsSidebar } from './components/SensorsSidebar/SensorsSidebar';
import { Grid } from '@mui/material';

const darkTheme = createTheme({
  palette: {
    mode: 'dark',
  },
});

type AppState = {
  selectedBuildingId: number
}
class App extends React.Component<{}, AppState> {

  state = {
    selectedBuildingId: 0
  }


  public render(): React.ReactNode {

    const setBuildingId = (id: number) => {
      this.setState({
        selectedBuildingId: id
      })
    }

    return (
      <ThemeProvider theme={darkTheme}>
        <CssBaseline />
        <Grid container justifyContent='space-between' width='98%' margin='auto' height='100vh' alignItems='center'>
          <Grid width='8%' item>
            <BuldingsSidebar setBuildingId={setBuildingId} />
          </Grid>
          <Grid item width='76%' maxHeight='90vh' overflow='auto' paddingRight='15px'>
            <Floors buildingId={this.state.selectedBuildingId} />
          </Grid>
          <Grid item width='12%' maxHeight='90vh' overflow='auto' paddingRight='15px'>
            <SensorsSidebar buildingId={this.state.selectedBuildingId}/>
          </Grid>
        </Grid>
      </ThemeProvider>
    );
  }
}

export default App;
