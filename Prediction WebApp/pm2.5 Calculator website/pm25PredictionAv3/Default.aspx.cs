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
            var client = new RestClient("https://ussouthcentral.services.azureml.net/workspaces/2925ec637804440e8a968080918b7775/services/63cdf886d22c441085c48b1ac1af75aa/execute?api-version=2.0&format=swagger");
            client.Timeout = -1;
            var request = new RestRequest(Method.POST);
            request.AddHeader("Content-Type", "application/json");
            request.AddHeader("Authorization", "Bearer sJ50wZb8uGgV8EFIamZuI+tY5dcpsZ2VkAhgmv+oJq0xF6ASfurz1uaBJ3CVgTlXfn7tjjpK4lgsWeYRKIDoLg==");
            request.AddHeader("Content-Type", "text/plain");
            request.AddParameter("application/json,text/plain", "{\n    \"Inputs\": {\n        \"input1\": [\n            {\n                \"Temperature\":" + inputTemperature.Text + ",\n                \"Humidity\":" + inputHumidity.Text + ",\n                \"CO2\":" + inputCO2.Text + "\n            }\n        ]\n    },\n    \"GlobalParameters\": {}\n}", ParameterType.RequestBody);
            IRestResponse response = client.Execute(request);
            Console.WriteLine(response.Content);

            var results = JObject.Parse(response.Content);
            string prediction = results["Results"]["output1"][0]["Scored Labels"].ToString();
            //labelResults.Text = Convert.ToDecimal(prediction).ToString("#0.##");
            labelResults.Text = prediction;
            
        } 
    } 
}