import requests

def postRequest(code, examination):
    end_point = 'http://localhost:8000/api/examine'

    data = {
        'code': code,
        'examination': examination
    }

    response = requests.post(end_point, data=data)

    print(f'Response {response}')

    if response.status_code == 200:
        print('Post request successfull')
    else:
        print('Fail to post data to the site')


postRequest(123234, 'data for test')