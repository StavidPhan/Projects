import openpyxl
import os
import sys
from datetime import datetime

a = 3
cur_date = datetime.now().day

wb = openpyxl.load_workbook('payroll.xlsx')
sheet = wb.active

sheet.cell(row = cur_date+2, column = 2).value = a

wb.save('payroll.xlsx')
wb.close()