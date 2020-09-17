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


#df.info()
#df.dtypes

df = df.fillna('')

#df['Unnamed4'] = df['Unnamed4'].fillna('')
df['SettPrice'] = df['Unnamed2'].astype(str) + df['Unnamed3'].astype(str) + df['Unnamed4'].astype(str) + ' ' + df['Unnamed5'].astype(str)

#TODO: remove unused lines

#pd.set_option('display.max_rows', len(df))
#print(df)
#pd.reset_option('display.max_rows')

#print(df.iloc[60])

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
