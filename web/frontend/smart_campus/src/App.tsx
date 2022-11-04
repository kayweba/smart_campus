import React from 'react';

import { ThemeProvider, createTheme } from '@mui/material/styles';

import './App.css';
import { RoomsComponent } from './components/Rooms/RoomsComponent';
import { BuildingComponent } from './components/Building/BuildingComponent';
import { BrowserRouter, Routes, Route } from 'react-router-dom'
import CssBaseline from '@mui/material/CssBaseline';

const darkTheme = createTheme({
  palette: {
    mode: 'dark',
  },
});

type AppState = {
  id_building: number
}

class App extends React.Component<{}, AppState> {

  state = {
    id_building: 0
  }

  public render(): React.ReactNode {

    const setBuildingId = (buildingId: number): void => {
      this.setState({
        id_building: buildingId
      })
    }


    return (
      <BrowserRouter>
        <ThemeProvider theme={darkTheme}>
          <CssBaseline />
          <Routes>
            <Route path='/' element={<BuildingComponent setBuildingId={setBuildingId} />} />
            <Route path='/building:id' element={<RoomsComponent idBuilding={this.state.id_building} />} />
          </Routes>
        </ThemeProvider>
      </BrowserRouter>
    );
  }
}

export default App;
