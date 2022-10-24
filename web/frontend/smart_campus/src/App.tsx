import React from 'react';

import { ThemeProvider, createTheme } from '@mui/material/styles';
import CssBaseline from '@mui/material/CssBaseline';

import './App.css';
import { RoomsComponent } from './components/Rooms/RoomsComponent';
import { Button } from '@mui/material';
import { Box } from '@mui/system';
import { ErrorReport } from './components/ErrorReport/ErrorReport';
import { ReportProvider } from './components/ReportProvider/ReportProvider';

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
        <ReportProvider>
          <ErrorReport />
          <RoomsComponent />
        </ReportProvider>
      </ThemeProvider>
    );
  }
}

export default App;
