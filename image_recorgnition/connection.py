import requests
import json

end_point = 'http://localhost:8000/api/check/'

def postRequest(json_data):
    data = json.dumps(json_data)
    response = requests.post(end_point, data=data, headers={'Content-Type': 'application/json'})
    return response.text