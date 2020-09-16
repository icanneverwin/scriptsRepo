import base64

import requests
import requests.auth
import json
import os
import csv
import datetime
import time
import collections



def load_audit(headers, in_filename):
    with open(in_filename, newline='') as csvfile:
        reader = csv.DictReader(csvfile)
        i = 0
        for row in reader:
            i = i + 1
            print(row['ticket_id'])
            url = "https://tescosupportcentre.zendesk.com/api/v2/tickets/" + row['ticket_id'] + "/audits.json"
            ii = 0
            while True:
                ii += 1
                print(str(i) + " " + str(ii))
                if (i + ii) % 100 == 0:
                    print('sleep')
                    time.sleep(60)
                response = requests.get(url, headers=headers)
                audit_json = response.json()
                if not os.path.isdir(("./" + queue + "/tickets_json")):
                    os.mkdir(("./" + queue + "/tickets_json"))
                f = open("./" + queue + "/tickets_json/" + row['ticket_id'] + "_" + str(ii) + ".txt", "a")
                f.write(json.dumps(audit_json) + '\n')
                f.close()
                url = audit_json.get("next_page")
                if url is None:
                    break


def parse_audit(ticket_list_filename, audit_filename, creators_filename):
    data = []
    creators = []
    path = "./" + queue + '/tickets_json'  # Define absolute path for directory with jsons
    with open(ticket_list_filename, newline='') as csvfile:
        reader = csv.DictReader(csvfile)
        for row in reader:
            print(row['ticket_id'], row['ticket_type'], row['ticket_priority'], row['ticket_type'])
            ii = 0
            while True:
                ii += 1
                cur_filename = path + "/" + row['ticket_id'] + "_" + str(ii) + ".txt"
                if os.path.exists(cur_filename):
                    # f = open(cur_filename, "r")
                    #ticket_json = json.loads(f.read())
                    ticket_json = [json.loads(line) for line in open(cur_filename, "r")]
                    for t in ticket_json[0].get("audits"):
                        case_id = t.get("ticket_id")
                        timestamp = t.get("created_at")
                        timestamp = timestamp.replace('T', ' ').replace('Z', ' ')
                        for e in t.get("events"):
                            if e.get("type") == "Create" and e.get("field_name") == "requester_id":
                                creators.append((case_id, e.get("value")))
                            if (e.get("type") == "Create" and e.get("field_name") == "group_id") or (
                                    e.get("type") == "Change" and e.get("field_name") == "group_id" and e.get(
                                "value") != e.get("previous_value")):
                                data.append(
                                    (case_id, e.get("value"), timestamp, row['ticket_type'], row['ticket_priority']))
                            if (e.get("type") == 'Change' and e.get("field_name") == "status" and e.get(
                                    "value") == "solved"):
                                data.append((case_id, "solved", timestamp, row['ticket_type'], row['ticket_priority']))
                    #f.close()
                else:
                    break
    with open(audit_filename, 'w', newline='', encoding='utf-8') as fp:
        writer = csv.writer(fp, delimiter=',')
        writer.writerow(["case_id", "activity", "timestamp", "ticket_type", "priority"])  # write header
        writer.writerows(data)

    with open(creators_filename, 'w', newline='', encoding='utf-8') as fp:
        writer = csv.writer(fp, delimiter=',')
        writer.writerow(["ticket_id", "user_id"])  # write header
        writer.writerows(creators)


def add_group_names(headers, in_filename, out_filename):
    data = []
    d = dict()
    s = set()
    url = "https://tescosupportcentre.zendesk.com/api/v2/groups/"
    with open(in_filename, newline='') as csvfile:
        reader = csv.DictReader(csvfile)
        for row in reader:
            s.add(row['activity'])
    i = 0
    for id in s:
        i += 1
        if i % 100 == 0:
            print('sleep')
            time.sleep(60)
        print(url + str(id) + ".json")
        response = requests.get(url + str(id) + ".json", headers=headers)
        l_json = response.json()
        try:
            d.update({id: l_json.get("group").get("name")})
        except:
            print("Error: " + str(id))
    with open(in_filename, newline='') as csvfile:
        reader = csv.DictReader(csvfile)
        for row in reader:
            if row['activity'] != 'solved':
                data.append((row['case_id'], d[row['activity']], row['timestamp'], row['activity'], row['ticket_type'],
                             row['priority']))
            else:
                data.append((row['case_id'], row['activity'], row['timestamp'], row['activity'], row['ticket_type'],
                             row['priority']))
    with open(out_filename, 'w', newline='', encoding='utf-8') as fp:
        writer = csv.writer(fp, delimiter=',')
        writer.writerow(["case_id", "activity", "timestamp", "group_id", "ticket_type", "priority"])  # write header
        writer.writerows(data)


def add_user_names(headers, in_filename, out_filename):
    data = []
    d = dict()
    s = set()
    url = url = "https://tescosupportcentre.zendesk.com/api/v2/users/"
    with open(in_filename, newline='') as csvfile:
        reader = csv.DictReader(csvfile)
        for row in reader:
            if (row['user_id']):
                s.add(row['user_id'])
    i = 0
    for id in s:
        i += 1
        if i % 100 == 0:
            print('sleep')
            time.sleep(60)
        print(url + str(id) + ".json")
        response = requests.get(url + str(id) + ".json", headers=headers)
        l_json = response.json()
        d.update({id: l_json.get("user").get("name")})
    with open(in_filename, newline='') as csvfile:
        reader = csv.DictReader(csvfile)
        for row in reader:
            if row['user_id']:
                data.append((row['ticket_id'], d[row['user_id']], row['user_id']))
    with open(out_filename, 'w', newline='', encoding='utf-8') as fp:
        writer = csv.writer(fp, delimiter=',')
        writer.writerow(["ticket_id", "user_name", "user_id"])  # write header
        writer.writerows(data)


if __name__ == "__main__":
    from creds import access_token, email
    creds = email + "/token:" + access_token

    conn_str = base64.b64encode(creds.encode()).decode("utf-8")
    headers = {"Authorization": "Basic " + conn_str}

    # path = "G:/My Drive/Scripts/python/ZD_Extract/175_StoreColleagueExperience_Newman"
    queue = "51_SSCFuel_Fuel"           # 01_Steria_Stock_OrderCalc, \
                                                # 175_StoreColleagueExperience_Newman, \
                                                # 01_Steria_Supplier_Depot_Order, \
                                                # 02_Steria_Customer_Order \
                                                # 25_Finance_Tender_Recon \
                                                # 30_myProductDeals \
                                                # 33_Steria_WMS_S_Denver \
                                                # 33_Steria_WMS_S_Solprint \
                                                # 51_SSCFuel_Fuel
                                                # 33_Steria_WMS_S_Langdon
                                                # 25_Steria_Finance_Financials
                                                # 05_Steria_Price
                                                # 49_Steria_MannedTills_Cash
                                                # 08_Steria_LocationService

    in_file = "./" + queue + "/" + queue + "_ticket_num_v0.1.csv"
    file_audit = "./" + queue + "/" + queue + "_audit.csv"
    file_creators = "./" + queue + "/" + queue + "_creators.csv"
    file_creators_named = "./" + queue + "/" + queue + "_creators_named.csv"
    file_data_au = "./" + queue + "/" + queue + "_data.csv"
    # ticket_list_file = "G:/My Drive/Scripts/python/ZD_Extract/01_Steria_Stock_OrderCalc/01_Steria_Stock_OrderCalc_ticket_num_v0.1.csv"

    load_audit(headers, in_file)
    parse_audit(in_file, file_audit, file_creators)
    add_group_names(headers, file_audit, file_data_au)
    add_user_names(headers, file_creators, file_creators_named)


    #url = "https://tescosupportcentre.zendesk.com/api/v2/tickets/" + "12774316" + "/audits.json"
    #response = requests.get(url, headers=headers)
    #audit_json = response.json()
    #print(audit_json)



    #data = [json.loads(line) for line in open("./25_Finance_Tender_Recon/tickets_json/13979067_1.txt", "r")]
    #print(data)
