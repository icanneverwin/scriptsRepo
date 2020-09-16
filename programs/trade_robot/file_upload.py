from ftplib import FTP
import os
from datetime import datetime
import re
import shutil

currentMonth = datetime.now().month
currentYear = datetime.now().year

currentFolder = str(currentYear) + '_' + str(currentMonth).rjust(2, '0')
print(currentFolder)


dest_dir = 'E:/Forex/bulletin_extracts'

def check_dir(directory: str) -> bool:
    if os.path.exists(directory):
        return True
    else:
        return False

def check_file(filename: str, directory: str) -> bool:
    if os.path.isfile(directory + '/' + filename):
        return True
    else:
        return False

def get_folder_name(filename: str) -> str:
    """[summary]

    Args:
        filename (str): name of the input file (expected bulletin archive)

    Returns:
        str: name of the folder 
    """
    match = re.search(r'(?<=pdf_)[0-9]{6}',filename)
    if match:
        return str(match.group(0)[:4]) + '_' + str(match.group(0)[4:])
    else:
        return 'None'

def get_files_for_upload(filelist: list) -> list:

    upload_files = list()
    for filename in filelist:
        file_path = dest_dir + '/' + get_folder_name(filename)
        if check_file(filename, file_path):
            print(f'File {filename} exists, continue...')
            continue
        else:
            print(f'{filename} is a new file, preparing for upload')
            upload_files.append(filename)
    
    return upload_files


def onetime_file_structure(directory: str):
    """
    1. go through all files in the folder
    2. for each identify creation date (using re)
    3. based on parsed date create folder YYYY_MM if not exists
    4. put the file into related folder
    """
  
    for filename in os.listdir(directory):
        current_path = directory + '/' + filename
        print(f'current_path = {current_path}')
        new_dir = get_folder_name(filename)

        if new_dir != 'None':
            destination_path = dest_dir + '/' + new_dir
            if check_dir(destination_path):
                # put file into this directory pass
                print(f"moving {filename} to {destination_path}")
                shutil.move(current_path, destination_path)
                #print(f'destination_path = {destination_path}')
            else:
                # create a new dir
                print(f"creating a new dir {destination_path}")
                os.mkdir(destination_path)
        else:
            print(f'could not match pattern to identify folder name, file {filename}')


def ftp_upload(server: str, directory='', interval=50):
    
    #ftp class set up
    ftp = FTP(server)
    ftp.login()
    ftp.cwd(directory)
    ftp_filenames = ftp.nlst()

    #check if main directory exist
    if not check_dir(dest_dir):
        os.mkdir(directory)

    upld_files = get_files_for_upload(ftp_filenames)

    for file in upld_files:
        temp_dir_name = get_folder_name(file)
        abs_dir_name = dest_dir + '/' + temp_dir_name
        if not check_dir(abs_dir_name):
            print(f"directory {abs_dir_name} does not exist. Creating...")
            os.mkdir(abs_dir_name)
        
        print(f'Downloading {file} ...')
        newfile = open(abs_dir_name + '/' + file, 'wb')
        ftp.retrbinary('RETR ' + file, newfile.write)
        newfile.close()
    
    ftp.close()
  

if __name__ == "__main__":
    ftp_upload("ftp.cmegroup.com", directory = 'bulletin')

    #print(os.listdir(dest_dir))
    # one time file correction in the folder E:\Forex\bulletin_extracts
    #onetime_file_structure(dest_dir)

    # file_list = ['DailyBulletin_pdf_20200601104.zip', 'DailyBulletin_pdf_20200602105.zip', 'DailyBulletin_pdf_20200603106.zip', 'DailyBulletin_pdf_20200604107.zip', 'DailyBulletin_pdf_20200605108.zip', 'DailyBulletin_pdf_20200608109.zip', 'DailyBulletin_pdf_20200609110.zip', 'DailyBulletin_pdf_20200610111.zip', 'DailyBulletin_pdf_20200611112.zip', 'DailyBulletin_pdf_20200612113.zip', 'DailyBulletin_pdf_20200615114.zip', 'DailyBulletin_pdf_20200616115.zip', 'DailyBulletin_pdf_20200617116.zip', 'DailyBulletin_pdf_20200618117.zip', 'DailyBulletin_pdf_20200619118.zip', 'DailyBulletin_pdf_20200622119.zip', 'DailyBulletin_pdf_20200623120.zip', 'DailyBulletin_pdf_20200624121.zip', 'DailyBulletin_pdf_20200625122.zip', 'DailyBulletin_pdf_20200626123.zip', 'DailyBulletin_pdf_20200629124.zip', 'DailyBulletin_pdf_20200630125.zip', 'DailyBulletin_pdf_20200701126.zip', 'DailyBulletin_pdf_20200702127.zip', 'DailyBulletin_pdf_20200706128.zip', 'DailyBulletin_pdf_20200707129.zip', 'DailyBulletin_pdf_20200708130.zip', 'DailyBulletin_pdf_20200709131.zip', 'DailyBulletin_pdf_20200710132.zip', 'DailyBulletin_pdf_20200713133.zip', 'DailyBulletin_pdf_20200714134.zip', 'DailyBulletin_pdf_20200715135.zip', 'DailyBulletin_pdf_20200716136.zip', 'DailyBulletin_pdf_20200717137.zip', 'DailyBulletin_pdf_20200720138.zip', 'DailyBulletin_pdf_20200721139.zip', 'DailyBulletin_pdf_20200722140.zip', 'DailyBulletin_pdf_20200723141.zip', 'DailyBulletin_pdf_20200724142.zip', 'DailyBulletin_pdf_20200727143.zip', 'DailyBulletin_pdf_20200728144.zip', 'DailyBulletin_pdf_20200729145.zip', 'DailyBulletin_pdf_20200730146.zip', 'DailyBulletin_pdf_20200731147.zip', 'DailyBulletin_pdf_20200803148.zip', 'DailyBulletin_pdf_20200804149.zip', 'DailyBulletin_pdf_20200805150.zip', 'DailyBulletin_pdf_20200806151.zip', 'DailyBulletin_pdf_20200807152.zip', 'DailyBulletin_pdf_20200810153.zip', 'DailyBulletin_pdf_20200811154.zip', 'DailyBulletin_pdf_20200812155.zip', 'DailyBulletin_pdf_20200813156.zip', 'DailyBulletin_pdf_20200814157.zip', 'DailyBulletin_pdf_20200817158.zip', 'DailyBulletin_pdf_20200818159.zip', 'DailyBulletin_pdf_20200819160.zip', 'DailyBulletin_pdf_20200820161.zip', 'DailyBulletin_pdf_20200821162.zip', 'DailyBulletin_pdf_20200824163.zip', 'DailyBulletin_pdf_20200825164.zip', 'DailyBulletin_pdf_20200826165.zip', 'DailyBulletin_pdf_20200827166.zip', 'DailyBulletin_pdf_20200828167.zip', 'DailyBulletin_pdf_20200831168.zip', 'DailyBulletin_pdf_20200901168.zip']

    #new_files = get_files_for_upload(file_list)
    #print(new_files)
