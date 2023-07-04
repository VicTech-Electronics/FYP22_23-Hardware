import requests

def post(plate_number):
    end_point = 'http://localhost/traffic/getdata.php?plate_number=' + plate_number
    response = requests.get(end_point)
    return response.text