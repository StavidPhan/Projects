import openpyxl
from datetime import datetime

cur_date = datetime.now().day

wb = openpyxl.load_workbook('payroll.xlsx')
sheet = wb.active

sheet.cell(row = cur_date, column = 3).value = 3

wb.save('payroll.xlsx')
wb.close()