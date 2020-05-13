<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="Default.aspx.cs" Inherits="pm25PredictionAv3.WebForm1" %>

<!DOCTYPE html>

<html xmlns="http://www.w3.org/1999/xhtml">

<head runat="server">
    <meta charset="utf-8"/>
    <meta name="viewport" content="width=device-width, initial-scale=1" />
    <meta name="theme-color" content="#000000" />
    <link rel="manifest" href="%PUBLIC_URL%/manifest.json" />
    <link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/bootstrap/4.3.1/css/bootstrap.min.css" integrity="sha384-ggOyR0iXCbMQv3Xipma34MD+dH/1fQ784/j6cY/iJTQUOhcWr7x9JvoRxT2MZw1T" crossorigin="anonymous"/>
    <link href="StyleSheet1.css" rel="stylesheet" type="text/css" />
    <title>Weather app</title>
</head>

<body>
      <div>
        <div class="wrapper">
          <div class="main">
            <div>
              <div class="row">
                <div class="col-5 title-container">
                    <div>
                        <h1 class="title-container__title">pm2.5 forecast</h1>
                        <h3 class="title-container__subtitle">Use this web app to forecast the upcoming pm2.5</h3>
                      </div>
                </div>

                <div class="col-7 form-container">
                    <form id="form1" runat="server">
                        <asp:TextBox ID="inputTemperature" runat="server" placeholder="23ºC"></asp:TextBox>
                        <asp:TextBox ID="inputHumidity" runat="server" placeholder="55%RH"></asp:TextBox>
                        <asp:TextBox ID="inputCO2" runat="server" placeholder="800ppm"></asp:TextBox>
                        <asp:Button ID="buttonPredict" runat="server" Text="Submit" OnClick="ButtonPredict_Click"/>
                      </form>

                    <div class="weather__info" id="outputdiv" runat="server">
                        <p class="weather__key">Temperature: <asp:Label ID="labelResults_temp" runat="server" class="weather__value" ></asp:Label> ºC</p>
                        <p class="weather__key">Humidity: <asp:Label ID="labelResults_humidity" runat="server" class="weather__value"></asp:Label> %RH</p>
                        <p class="weather__key">CO2: <asp:Label ID="labelResults_co2" runat="server" class="weather__value"></asp:Label> ppm</p>
                        <p class="weather__key">pm2.5: <asp:Label ID="labelResults_pm25" runat="server" class="weather__value"></asp:Label> ppm</p>
                    </div>
                </div>

              </div>
            </div>
          </div>
        </div>
      </div>
</body>
</html>