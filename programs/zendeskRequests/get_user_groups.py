import requests
import json
import base64
import csv

from creds import access_token, email

credentials = email+"/token:"+ access_token
conn_str = base64.b64encode(credentials.encode()).decode("utf-8")
headers = {"Authorization": "Basic "+ conn_str}


def file_load(filename:str) -> list:
    with open(filename, 'r') as infile:
        email_list = [line.rstrip() for line in infile]
    
    return email_list


def get_user_id(header: str, emails: list) -> dict:
    userIds = {}
    emailCount = len(emails)

    # go through all input emails
    for i in range(emailCount):
        url = 'https://tescosupportcentre.zendesk.com//api/v2/search.json?query=type:user "'+ emails[i] + '"'
        response = requests.get(url, headers=headers)
        data = response.json()

        #go through all possible ids and attach to dict ("email": [ids])
        for j in data.get("results"):
            userIds.setdefault(emails[i], []).append(j.get("id"))

    return userIds


def get_user_groups(header: str, ids: dict) -> dict:
    userGroups = dict()

    # go through each element in the dict
    for key, value in ids.items():
        # go through each id as per email
        ids_len = len(value)
        for i in range(ids_len):
            url = "https://tescosupportcentre.zendesk.com/api/v2/users/"+ str(value[i]) +"/groups.json"
            response = requests.get(url, headers=headers)
            data = response.json()
            for j in data.get("groups"):
                userGroups.setdefault(key, []).append(j.get("name"))
    
    return userGroups




def write_in_file(userGroups: dict, filename: str):
    with open(filename, 'w', newline='') as wf:
        writer = csv.writer(wf)
        csvHeader = ['email', 'groupname']
        writer.writerow(csvHeader)
        for key, value in userGroups.items():
            writer.writerow([key, value])


def main(filename):


    email_list = file_load(filename)
    userIds = get_user_id(headers, email_list)
    userGroups = get_user_groups(headers, userIds)
    write_in_file(userGroups, 'usergroups.csv')


if __name__ == "__main__":

    filename = 'G:/My Drive/Tasks/AMS_Strategy/emails.txt'
    main(filename)