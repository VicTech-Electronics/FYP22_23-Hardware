import requests
import json

def postRequest(code, examination):
    end_point = 'http://localhost:8000/api/examine/'

    data = {
        'code': code,
        'examination': examination
    }

    json_data = json.dumps(data)

    response = requests.post(end_point, data=json_data, headers={'Content-Type': 'application/json'})

    if response.status_code == 200:
        print('Post request successfull')
    elif response.status_code == 404:
        print(f'Patient of code {code}, not exists in our records')
    else:
        print('Fail to post data to the site')

    return response
