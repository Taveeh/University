import React, { Component } from 'react';
import './App.css';
import Menu from "./components/Menu/Menu";
import { Container, Row, Col } from "reactstrap";

class App extends Component {

  componentDidMount() {
    document.body.style = 'background-color: #2a93d5;';
  }

  render() {
    return (
      <div className="App">

      </div>
    );
  }
}

export default App;