# link tham khảo grid: https://www.pythontutorial.net/tkinter/tkinter-grid/

from tkinter import *
from tkinter import scrolledtext
from selenium import webdriver
import time

def initDriver():
	option = webdriver.EdgeOptions()
	option.add_argument("--user-data-dir=C:\\Users\\ThanhDuy\\AppData\\Local\\Microsoft\\Edge\\User Data")
	option.add_argument("--profile-directory=" + profile_box.get())
	driver = webdriver.ChromiumEdge(executable_path="D:\\Projects\\Chrome Selenium\\msedgedriver.exe", options=option)
	return driver

def open_web():
	driver = initDriver()
	link_list = data.get(1.0, END).split('\n')
	for i in range(len(link_list)):
		driver.execute_script("window.open('')")
		driver.switch_to.window(driver.window_handles[i+1])
		driver.get(link_list[i])	
	time.sleep(500)


def clearData():
    data.delete(1.0,END)


root = Tk()
root.geometry('670x310')
root.title('AUTO OPEN WEB')
root.configure(bg = 'lavender')

profile_box = Spinbox(root, values=("Default", "Profile 9", "Profile 10", "Profile 11", "Profile 12", "Profile 13", "Profile 14", "Profile 15", "Profile 16", "Profile 17", "Profile 18", "Profile 19", "Profile 21", "Profile 22", "Profile 23", "Profile 24"))
profile_box.grid(row=0, column=2)

data = scrolledtext.ScrolledText(root,width=80,height=17)
data.grid(column=0, row=2, columnspan=3)

buttonSTART = Button(root, text="START", command=open_web).grid(row=0, column=1)
buttonClear = Button(root, text="Clear Data", command=clearData).grid(row=0, column=0)

root.mainloop()
