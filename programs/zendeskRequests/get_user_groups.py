import requests
import json
import base64
import csv
import time

from requests.models import Response

from creds import access_token, email

credentials = email+"/token:"+ access_token
conn_str = base64.b64encode(credentials.encode()).decode("utf-8")
headers = {"Authorization": "Basic "+ conn_str}


def file_load(filename:str) -> list:
    """This function gets csv file with the following structure:
            email
            email
            ....
        and parses emails into list.

    Args:
        filename (str): csv file

    Returns:
        list: output list
    """

    with open(filename, 'r') as infile:
        output_list = [line.rstrip() for line in infile]
    
    return output_list


def get_user_id(header: str, emails: list) -> dict:
    """
        get_user_id extracts Zendesk user Ids based on input email list

    Args:
        header (str): request header
        emails (list): user emails

    Returns:
        dict: {email: userId}
    """

    userIds = {}
    emailCount = len(emails)

    # go through all input emails
    for i in range(emailCount):
        url = 'https://tescosupportcentre.zendesk.com/api/v2/search.json?query=type:user "'+ emails[i] + '"'
        response = requests.get(url, headers=headers)
        data = response.json()

        #go through all possible ids and attach to dict ("email": [ids])
        for j in data.get("results"):
            userIds.setdefault(emails[i], []).append(j.get("id"))

    return userIds


def get_user_groups(header: str, ids: dict) -> dict:
    """get_user_groups requests ZD groups attached to input userId 

    Args:
        header (str): request header
        ids (dict): ZD userID

    Returns:
        dict: {email: [userGroups]}
    """

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
    """write_in_file creates a new file with the following structure: email, groups 

    Args:
        userGroups (dict): {email: [userGroups]}
        filename (str): file to be created
    """
    with open(filename, 'w', newline='', encoding='utf-8') as wf:
        writer = csv.writer(wf)
        csvHeader = ['groupname', 'user']
        writer.writerow(csvHeader)
        for key, value in userGroups.items():
            for i in range(len(value)):
                writer.writerow([key, value[i]])


def get_users_in_group(header: str, groupnames: list) -> dict:
    """get_users_in_group extracts userIds attached to the ZD group

    Args:
        header (str): request header
        groupnames (list): list of ZD groups

    Returns:
        dict: {groupname: [userIds]}
    """
    
    groupIds = {}
    groupUserIds = {}
    groupUserEmails = {}
    requestCount = 0

    # get groupId by its name
    for group in groupnames:
        url = 'https://tescosupportcentre.zendesk.com/api/v2/search.json?query=type:group "' + group + '"'
        if requestCount != 0 and requestCount % 100 == 0:
            print(f'requestCount = {requestCount}, sleeping...')
            time.sleep(60)
        response = requests.get(url, headers=headers)
        requestCount += 1
        data = response.json()
        groupIds[group] = data.get('results')[0].get('id')

    # get group membership
    for key, value in groupIds.items():
        url = 'https://tescosupportcentre.zendesk.com/api/v2/groups/' + str(value) + '/memberships.json'
        if requestCount != 0 and requestCount % 100 == 0:
            print(f'requestCount = {requestCount}, sleeping...')
            time.sleep(60)
        response = requests.get(url, headers=headers)
        requestCount += 1
        data = response.json()

        for user in data.get('group_memberships'):
            groupUserIds.setdefault(key, []).append(user.get('user_id'))

    # get user emails per id and assign to dict

    # 1st loop over each group
    for key, value in groupUserIds.items():

        # 2nd loop over each user in the group
        for user in value:
            url = 'https://tescosupportcentre.zendesk.com/api/v2/users/' + str(user) + '.json'
            if requestCount != 0 and requestCount % 100 == 0:
                print(f'requestCount = {requestCount}, sleeping...')
                time.sleep(60)
            response = requests.get(url, headers=headers)
            requestCount += 1
            data = response.json()

            if data.get('user').get('email') == None:
                groupUserEmails.setdefault(key, []).append(data.get('user').get('name'))
            else:
                groupUserEmails.setdefault(key, []).append(data.get('user').get('email'))

    print(f'Total count of requests is: {requestCount}')
    return groupUserEmails


def main(filename):


    email_list = file_load(filename)
    userIds = get_user_id(headers, email_list)
    userGroups = get_user_groups(headers, userIds)
    write_in_file(userGroups, 'usergroups.csv')


if __name__ == "__main__":

    #filename = 'G:/My Drive/Tasks/AMS_Strategy/emails.txt'
    #main(filename)

    ###################################################################################
    #  extracting user that are attached to input groupnames
    ###################################################################################
    #group = ['27_property_SRDGROUP_CRDB', '86_Platform_Backup_ASIA', '27_property_SRDGROUP_IKB']
    
    filename = 'G:/My Drive/Tasks/AMS_Strategy/groups1.txt'
    groups = file_load(filename)
    groupUsers = get_users_in_group(headers, groups)
    write_in_file(groupUsers, 'groupsUsers6.csv')

    # user = 361647592760
    # url = 'https://tescosupportcentre.zendesk.com/api/v2/users/' + str(user) + '.json'
    # response = requests.get(url, headers=headers)
    # data = response.json()
    # 
    # users = dict()
    # 
    # if data.get('user').get('email') == None:
    #     users[user] = data.get('user').get('name')
    # else:
    #     users[user] = data.get('user').get('email')

    # print(data)
    # print(users)


    ###################################################################################
    # test on extracting groups from ZD
    ###################################################################################
    # filename = 'G:/My Drive/Tasks/AMS_Strategy/groups.txt'
    # groups = file_load(filename)
    # 
    # groupIds = {}
    # requestCount = 0
    # 
    # # get groupId by its name
    # for group in groups:
    #     url = 'https://tescosupportcentre.zendesk.com/api/v2/search.json?query=type:group "' + group + '"'
    #     if requestCount != 0 and requestCount % 100 == 0:
    #         print(f'requestCount = {requestCount}, sleeping...')
    #         time.sleep(60)
    #     response = requests.get(url, headers=headers)
    #     requestCount += 1
    #     data = response.json()
    #     groupIds[group] = data.get('results')[0].get('id')
    # 
    # print(groupIds)


    ###################################################################################


    #group = 'Retail ST Implementations'
    #url = 'https://tescosupportcentre.zendesk.com/api/v2/search.json?query=type:group "' + group + '"'
    #response = requests.get(url, headers=headers)
    #data = response.json()
    #print(data)