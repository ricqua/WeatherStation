<%-- https://www.youtube.com/watch?v=nnOFdri97rM&t=68s --%>

<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="Default.aspx.cs" Inherits="pm25PredictionAv3.WebForm1" %>

<!DOCTYPE html>

<html xmlns="http://www.w3.org/1999/xhtml">

<head runat="server">
    <title>pm25PredictionAv3</title>
    <style>
        body {font-family: Arial; font-size: 12px;}
    </style>
</head>

<body>
    <form id="form1" runat="server">
        <div style="padding: 5px 15px 5px 15px; background:; background-color: #0066CC; color: #FFFFFF;">
            <h1>PM2.5 Calculator</h1>
            <p style="text-align: justify">
                This tool makes use of a machine learning model trained using "Azure - Machine Learning Studio" 
                to evaluate user submited weather data in order to predict air pollution values.  
                All data used to train the models were collected by the authors using various sensors 
                connected to an Arduino Mega.
                Data used to train the model was collected in Seoul, South Korea between 1 January 2020 - 1 March 2020.
            </p>
        </div>     
        <br/>
        <div style="padding: 5px 15px 5px 15px;">
            <table>
                <tr>
                    <th style="padding: 0px 20px 0px 0px;">Temperature (ºC)</th>
                    <td><asp:TextBox ID="inputTemperature" runat="server"></asp:TextBox></td>
                </tr>
                <tr>
                    <th style="text-align: left">Humidity (%RH)</th>
                    <td><asp:TextBox ID="inputHumidity" runat="server"></asp:TextBox></td>
                </tr>
                <tr>
                    <th style="text-align: left">CO2 (ppm)</th>
                    <td><asp:TextBox ID="inputCO2" runat="server"></asp:TextBox></td>
                </tr>
                <tr>
                    <th></th>
                    <th><asp:Button ID="buttonPredict" runat="server" Text="Submit" OnClick="buttonPredict_Click" BackColor="#009933" ForeColor="White" Font-Size="12pt"/></th>
                    </tr>
            </table>
        </div>
        <br />
        <div style="padding: 5px 15px 5px 15px; border: 1px solid #000000; color: #000000;">
            <table>
                <tr >
                    <th style="padding-right:10px">Predicted PM2.5 (ppm):</th>
                    <td><asp:Label ID="labelResults" runat="server" Text="-" Font-Size="12pt" ></asp:Label></td>
                </tr>
            </table>
        </div>
        
        
    </form>
</body>
</html>