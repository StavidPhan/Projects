def get_postUID(s):
    if len(s)>35:
        a = s.index('/',len(s)-20, len(s)-1)
        b = s.find('/',a+6, len(s)-1)
        if b == -1:
            return s[a+1:len(s)-1]
        else:
            return s[a+1:b]


def get_groupUID(s):
    if len(s)>35:
        a = s.index('/',30, 40)
        b = s.index('/',40, 54) 
        return s[a+1:b]
    

with open('H:/My Drive/exe/MaxCare/MaxCare_V4.9.0/__UID.txt', mode='r+', encoding = 'utf-8') as f:
    data = f.readlines()
    for i in data:
        if len(i)>35:
            f.write(get_postUID(i))
            print(get_postUID(i))
            #f.write(get_groupUID(i))
            f.write("\n")
