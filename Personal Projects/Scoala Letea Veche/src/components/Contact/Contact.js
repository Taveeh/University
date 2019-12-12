import React from 'react';
import { Container, Row, Col } from 'reactstrap';
import './Contact.css';
import { Map, GoogleApiWrapper, Marker } from 'google-maps-react';


class About extends React.Component {

    componentDidMount() {
        document.body.style = 'background-color: #d8f7f9;';
    }

    render() {
        return (
            <Map google={this.props.google} zoom={14}>
                <Marker name={'Current location'} position={{ lat: 46.5533801, lng: 26.9446409 }} />
            </Map>
        )
    }
}

export default GoogleApiWrapper({
    apiKey: "AIzaSyBe3gz9Xq74lAha1ODnLbQHlG2cWkBT4Fg"
})(About)