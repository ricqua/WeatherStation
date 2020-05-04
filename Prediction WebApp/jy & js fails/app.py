import urllib.request
import json

data = {
    "Inputs": {
        "input1":
        [
            {
                'Temperature': "23.2",
                'Humidity': "53.6",
                'CO2': "388",
            }
        ],
},
    "GlobalParameters": {
    }
}

body = str.encode(json.dumps(data))

url = "https://ussouthcentral.services.azureml.net/workspaces/2925ec637804440e8a968080918b7775/services/63cdf886d22c441085c48b1ac1af75aa/execute?api-version=2.0&format=swagger"
api_key = 'sJ50wZb8uGgV8EFIamZuI+tY5dcpsZ2VkAhgmv+oJq0xF6ASfurz1uaBJ3CVgTlXfn7tjjpK4lgsWeYRKIDoLg=='
headers = { 'Content-Type': 'application/json', 'Authorization': ('Bearer ' + api_key) }

req = urllib.request.Request(url, body, headers)

try:
    response = urllib.request.urlopen(req)

    result = response.read()
    #print(result)
except urllib.error.HTTPError as error:
    print("The request failed with status code: " + str(error.code))

# Print the headers - they include the requert ID and the timestamp, which are useful for debugging the failure
# print(error.info())
# print(json.loads(error.read().decode("utf8", 'ignore')))

y = json.loads(result)
float Temperature = y["Results"]['output1'][0]['Temperature']
float Humidity = y["Results"]['output1'][0]['Humidity']
float CO2 = y["Results"]['output1'][0]['CO2']
float ScoredLabel = str(round(float(y["Results"]['output1'][0]['Scored Labels'])))

print(ScoredLabel)


# print("Temperature: " + Temperature + "ºC,  Humidity: " + Humidity + "RH%,  CO2: " + CO2 + "ppm,  PM2.5: " + ScoredLabel + "ppm")

