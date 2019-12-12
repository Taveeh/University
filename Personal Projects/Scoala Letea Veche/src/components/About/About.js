import React from 'react';
import { Container, Row, Col } from 'reactstrap';
import './About.css';
import director from "../../assets/director.jpg";

class About extends React.Component {

    componentDidMount() {
        document.body.style = 'background-color: #2a93d5;';
    }

    render() {
        return (
            <div className="About">
                <Container>
                    <Row>
                        <Col xs="2" sm='1'></Col>
                        <Col xs="8" sm='10'>
                            <div id="aboutText">
                                <p>&#350;coala Letea Veche este o unitate de &#238;nv&#259;&#539;&#259;m&#226;nt cu tradi&#539;ie, fiind &#238;nfiin&#539;at&#259; din anul 1865. &#206;n anul 1891 s-a construit localul propriu al &#x219;colii, cl&#259;dire &#238;n care s-a &#238;nv&#259;&#539;at p&#226;n&#259; &#238;n anul 1972, c&#226;nd s-a inaugurat actualul local al &#x219;colii. Cl&#259;direa &#238;n care func&#539;ioneaz&#259; &#x219;coala &#238;n prezent este modern&#259;, cu etaj, cu 8 s&#259;li de clas&#259;, laborator de fizic&#259;-chimie, cabinet de informatic&#259;, bibliotec&#259; cu 8000 volume, sal&#259; de sport.</p><p> De-a lungul timpului, &#238;n aceast&#259; &#x219;coal&#259; au profesat cadre didactice de renume, care au f&#259;cut faim&#259; &#x219;colii b&#259;c&#259;uane. De pe b&#259;ncile &#x219;colii noastre au ie&#x219;it an de an, elevi care mai t&#226;rziu au ajuns profesori, medici sau ingineri renumi&#539;i sau pur &#x219;i simplu oameni de valoare ai societ&#259;&#539;ii. Toate acestea au f&#259;cut ca aceast&#259; &#x219;coal&#259; s&#259; se bucure de un respect deosebit &#238;n cadrul comunit&#259;&#539;ii.</p>
                                <p>
                                    Colectivul didactic de ast&#259;zi  &#238;mbin&#259; fericit entuziasmul tiner&#539;ii cu experien&#539;a cadrelor didactice mai &#238;n v&#226;rst&#259;, &#238;ncerc&#226;nd prin modul &#238;n care &#238;&#x219;i &#238;ndepine&#x219;te misiunea s&#259; duc&#259; mai departe buna tradi&#539;ie a &#x219;colii &#x219;i s&#259; impun&#259; &#238;n comunitate respectul &#x219;i considera&#539;ia de care s-a bucurat &#238;n trecut. Atmosfera &#238;n &#x219;coal&#259; este pl&#259;cut&#259;, destins&#259;, propice unui proces instructiv-educativ de calitate. Aceast&#259; atmosfer&#259; este transmis&#259; elevilor &#x219;i &#238;ntregii comunit&#259;&#539;i. </p>
                                <p>
                                    &#350;coala Letea Veche are misiunea de a oferi educa&#539;ie &#x219;i instruc&#539;ie tuturor celor care apeleaz&#259; la serviciile &#x219;colii, indiferent de v&#226;rst&#259; (copii, tineri, adul&#539;i), etnie, orientare religioas&#259;, elimin&#226;nd orice form&#259; de discriminare. &#350;coala este un centru cultural al comunit&#259;&#539;ii, pune la dispozi&#539;ie toate resursele umane, materiale, curriculare &#238;n concordan&#539;&#259; cu evolu&#539;ia societ&#259;&#539;ii, &#238;n spiritul progresului &#x219;i civiliza&#539;iei . Asigur&#259; o educa&#539;ie de calitate pentru dezvoltarea copiilor(3-14 ani), &#238;n vederea integr&#259;rii acestuia &#238;n plan social, pentru a deveni cet&#259;&#539;eni activi &#x219;i responsabili, deplin con&#x219;tien&#539;i de propria lor valoare, cu o serie de cunostinte &#x219;i abilit&#259;&#539;i practice insu&#351;ite, necesare pentru integrarea &#238;n context socio-profesional.
                                </p>
                            </div>
                        </Col>
                        <Col xs="2" sm='1'></Col>
                    </Row>
                    <Row>
                        <Col xs="0" md="1"></Col>
                        <Col xs="12" md="4" style={{ textAlign: 'center' }}>
                            <p> DIRECTOR: Custura Mihaela </p>
                            <img alt="director" className="director" src={director} />
                        </Col>
                        <Col xs="0" md="2"></Col>
                        <Col xs="12" md="4" style={{ textAlign: 'center' }}>
                            <p> Secretar: Nume Prenume </p>
                            <img alt="secretar" className="secretar" src={director} />
                        </Col>
                        <Col xs="0" md="1"></Col>
                    </Row>
                </Container>
            </div>
        )
    }
}

export default About;