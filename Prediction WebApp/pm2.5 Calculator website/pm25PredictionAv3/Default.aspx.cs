using System;
using RestSharp;
using Newtonsoft.Json.Linq;

namespace pm25PredictionAv3
{
    public partial class WebForm1 : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e){
                   }

        protected void ButtonPredict_Click(object sender, EventArgs e){
            var client = new RestClient("https://ussouthcentral.services.azureml.net/workspaces/2925ec637804440e8a968080918b7775/services/63cdf886d22c441085c48b1ac1af75aa/execute?api-version=2.0&format=swagger");
            //var client = new RestClient("http://52.231.76.170:80/api/v1/service/ricqua-microdustav1-endpoint1/score");
            client.Timeout = -1;
            var request = new RestRequest(Method.POST);
            request.AddHeader("Content-Type", "application/json");
            request.AddHeader("Authorization", "Bearer sJ50wZb8uGgV8EFIamZuI+tY5dcpsZ2VkAhgmv+oJq0xF6ASfurz1uaBJ3CVgTlXfn7tjjpK4lgsWeYRKIDoLg==");
            //request.AddHeader("Authorization", "Bearer bykddjziDfoNcf2q0HC6tkTlGVJxHYum");
            request.AddHeader("Content-Type", "text/plain");
            request.AddParameter("application/json,text/plain", "{\n    \"Inputs\": {\n        \"input1\": [\n            {\n                \"Temperature\":" + inputTemperature.Text + ",\n                \"Humidity\":" + inputHumidity.Text + ",\n                \"CO2\":" + inputCO2.Text + "\n            }\n        ]\n    },\n    \"GlobalParameters\": {}\n}", ParameterType.RequestBody);
            IRestResponse response = client.Execute(request);
            Console.WriteLine(response.Content);

            var results = JObject.Parse(response.Content);

            labelResults_temp.Text = results["Results"]["output1"][0]["Temperature"].ToString();
            labelResults_humidity.Text = results["Results"]["output1"][0]["Humidity"].ToString();
            labelResults_co2.Text = results["Results"]["output1"][0]["CO2"].ToString();
            labelResults_pm25.Text = results["Results"]["output1"][0]["Scored Labels"].ToString();
            
        }
    } 
}