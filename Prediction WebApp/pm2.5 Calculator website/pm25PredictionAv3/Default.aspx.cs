using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using RestSharp;
using Newtonsoft.Json.Linq;

namespace pm25PredictionAv3
{
    public partial class WebForm1 : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e){
                   }

        protected void buttonPredict_Click(object sender, EventArgs e)
        {
            var client = new RestClient("https://ussouthcentral.services.azureml.net/workspaces/2925ec637804440e8a968080918b7775/services/4b21b724d795439ab1e8c4b0b0fcb4ef/execute?api-version=2.0&details=true");
            client.Timeout = -1;
            var request = new RestRequest(Method.POST);
            request.AddHeader("Authorization", "Bearer gC1asyN3yggFsxsbUXf0ZAEFNkIaCaPKZR32T06OEp7ZewdSai4zMMBXNN+IdchKj4bENdOqTwAklwxzKsvFIw==");
            request.AddHeader("Content-Type", "application/json");
            request.AddParameter("application/json,text/plain", "{\r\n  \"Inputs\": {\r\n    \"input1\": {\r\n      \"ColumnNames\": [\r\n        \"Temperature\",\r\n        \"Humidity\",\r\n        \"CO2\"\r\n      ],\r\n      \"Values\": [\r\n        [\r\n          \"" + inputTemperature.Text + "\",\r\n          \"" + inputHumidity.Text + "\",\r\n          \"" + inputCO2.Text + "\"\r\n        ],\r\n      ]\r\n    }\r\n  },\r\n  \"GlobalParameters\": {}\r\n}", ParameterType.RequestBody);
            IRestResponse response = client.Execute(request);
            Console.WriteLine(response.Content.ToString());
            //labelResults.Text = response.Content.ToString();

            var results = JObject.Parse(response.Content);
            string prediction = results["Results"]["output1"]["value"]["Values"].ToString();
            prediction = prediction.Replace("[", "").Replace("]", "").Replace("\"", "");
            labelResults.Text = prediction;
            //labelResults.Text = Convert.ToDecimal(prediction).ToString("#0.##");
        } 
    } 
}