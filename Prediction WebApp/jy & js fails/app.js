// var submitButton = document.getElementById('submitButton');

let req = require("request");
let temp;
let humi = 0;
let co2 = 0;
let pm25 = 0;

const uri =
  "https://ussouthcentral.services.azureml.net/workspaces/2925ec637804440e8a968080918b7775/services/63cdf886d22c441085c48b1ac1af75aa/execute?api-version=2.0&format=swagger";
const apiKey =
  "sJ50wZb8uGgV8EFIamZuI+tY5dcpsZ2VkAhgmv+oJq0xF6ASfurz1uaBJ3CVgTlXfn7tjjpK4lgsWeYRKIDoLg==";

let data = {
  Inputs: {
    input1: [
      {
        Temperature: 23,
        Humidity: 55,
        CO2: 1000,
      },
    ],
  },
  GlobalParameters: {},
};

// {Inputs:{input1:[{Temperature:23,Humidity:55,CO2:1000,},], }, GlobalParameters: {}, }

const options = {
  uri: uri,
  method: "POST",
  headers: {
    "Content-Type": "application/json",
    Authorization: "Bearer " + apiKey,
    "Content-Length": data.length,
  },
  body: JSON.stringify(data),
};

req(options, (err, res, body) => {
  if (!err && res.statusCode == 200) {
    body = JSON.parse(body);
    //console.log(body);

    pm25 = body["Results"]["output1"][0]["Scored Labels"];
    // pm25 = body["Results"]["output1"][0]["CO2"];
    console.log(pm25);

    // document.getElementById('pm25Output') = pm25;
  } else {
    console.log("The request failed with status code: " + res.statusCode);
  }
});
