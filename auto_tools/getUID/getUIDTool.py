from tkinter import *
from tkinter import scrolledtext


def get_postUID():
    a = data.get(1.0, END).split('\n')
    for s in a:
        if len(s)>35:
            a = s.index('/',len(s)-20, len(s)-1)
            b = s.find('/',a+6, len(s))
            if b == -1:
                uid.insert(INSERT, s[a+1:len(s)]) 
                uid.insert(INSERT, '\n') 
            else:
                uid.insert(INSERT, s[a+1:b])
                uid.insert(INSERT, '\n')


def clear_data():
    data.delete(1.0,END)


def clear_uid():
    uid.delete(1.0,END)


root = Tk()
root.geometry('740x540')
root.title('PHÂN MỀM SEEDING')
root.configure(bg = 'lavender')

# init Label
Label(root, text='Data', bg='lavender').grid(row=0, column=0)
Label(root, text='UID', bg='lavender').grid(row=0, column=60)

# init scrolledtext
data = scrolledtext.ScrolledText(root,width=40,height=30)
data.grid(column=0, row=2)
uid = scrolledtext.ScrolledText(root,width=40,height=30)
uid.grid(column=60, row=2)

# init Button
buttonGetUID = Button(root, text="GET UID", command=get_postUID).grid(row=0, column=30)
buttonClearData = Button(root, text="Clear Data", command=clear_data).grid(row=4, column=0)
buttonClearUID = Button(root, text="Clear UID", command=clear_data).grid(row=4, column=60)

root.mainloop()