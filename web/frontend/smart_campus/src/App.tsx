import React from 'react';

import { ThemeProvider, createTheme } from '@mui/material/styles';
import CssBaseline from '@mui/material/CssBaseline';

import './App.css';
import { RoomsComponent } from './components/Rooms/RoomsComponent';

    const darkTheme = createTheme({
      palette: {
        mode: 'dark',
      },
    });

class App extends React.Component {

  public render(): React.ReactNode {
    return (
      <ThemeProvider theme={darkTheme}>
         <CssBaseline />
        <RoomsComponent />
      </ThemeProvider>
    );
  }
}

export default App;
