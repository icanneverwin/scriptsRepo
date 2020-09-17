import tabula
import pandas as pd
import csv

#tabula.environment_info()

pdf_file = 'E:/Forex/bulletin_extracts/2020_09/Section07_Currency_Futures.pdf'

pdf_file_path = 'E:/Forex/bulletin_extracts/2020_09/'
pdf_name = 'Section07_Currency_Futures.pdf'
csv_name = 'Section07_Currency_Futures.csv'
#pdf_to_csv = tabula.read_pdf(pdf_file, stream=True, pandas_options={'header': None})


#df.info()

tabula.convert_into(pdf_file_path + pdf_name, pdf_file_path + csv_name, output_format='csv')

df = pd.read_csv(pdf_file_path + csv_name,header=None)
df.columns = [  'Date',
                'Unnamed1', 
                'GlobexHigh',
                'GlobexLow', 
                'Unnamed2', 
                'Unnamed3',
                'Unnamed4',
                'Unnamed5',
                'RTHVolume',
                'GlobexVolume',
                'OpenInterestTotal',
                'OpenInterestChange',
                'Contract' #ContractHigh, ContractLow
            ]
#df['Unnamed4'] = df['Unnamed4'].fillna('')
df['SettPrice'] = df['Unnamed2'].astype(str) + df['Unnamed3'].astype(str) + df['Unnamed4'].astype(str) + ' ' + df['Unnamed5'].astype(str)

# overall info
#df.info()
#df.dtypes
#df.describe()

df = df.fillna('')

#TODO: remove unused lines

# read headers
df.columns
cols = df.columns.values # get list of column names

# read each column
print(df['SettPrice'])
print(df[['SettPrice', 'GlobexLow', 'GlobexVolume']])

# read each row
print(df.iloc[1])
print(df.iloc[1:4])

# read a specific location
print(df.iloc[2,1])

#for index, row in df.iterrows():
#    print(index, row)

# show top/tail 5

df.head(5)
df.tail(5)

# df = df.drop(columns=['Unnamed2']) # drop columns

#df['Total'] = df.iloc[:, 4:19].sum(axis=1) # new total = sum(4:9) - for each row

#df = df.reset_index() # reset index

#pd.set_option('display.max_rows', len(df))
#print(df)
#pd.reset_option('display.max_rows')

#print(df.iloc[60])

# find cells that contain the value:

df.loc[df['Date'].str.contains('TOTAL')]

print(df.loc[df['Date'] == 'TOTAL  SWISS FRNC FUT'])

#df.to_csv(pdf_file_path + 'test.csv')

#with open(pdf_file_path + csv_name) as file:
#    print(file.readline())




def remove_lines_from_csv(filename: str, start_p: str, ):
    str_p = 'EX-PIT & OTHER BREAKDOWN'

    #with open(filename)






#new_file = open('E:/Forex/bulletin_extracts/2020_09/data.json', 'w')
#new_file.write(str(df))
#new_file.close()
