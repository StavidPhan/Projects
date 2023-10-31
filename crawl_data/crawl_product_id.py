from http import cookies
import requests
import time
import random
import pandas

'''cookies = {
    '_trackity': '7efb4338-41ed-96b9-f796-785783de9f4c',
    'TOKENS': '{%22access_token%22:%22Hkj5dnVZgsBb2r9SDhAGxpowKW0YQXeN%22%2C%22expires_in%22:157680000%2C%22expires_at%22:1825129724334%2C%22guest_token%22:%22Hkj5dnVZgsBb2r9SDhAGxpowKW0YQXeN%22}',
    '_gid': 'GA1.2.1450693154.1667449728',
    '_gac_UA-15036050-1': '1.1667449728.Cj0KCQjwqoibBhDUARIsAH2OpWhfKJYwjKaGPcEiUsbB-c-zVZbDPbY0DuIptDFq4e7sOVbxhYzBro0aAo4vEALw_wcB',
    'delivery_zone': 'Vk4wMzQwMjQwMTM=',
    'tiki_client_id': '1196941600.1667449728',
    '_gat': '1',
    '_gcl_aw': 'GCL.1667449732.Cj0KCQjwqoibBhDUARIsAH2OpWhfKJYwjKaGPcEiUsbB-c-zVZbDPbY0DuIptDFq4e7sOVbxhYzBro0aAo4vEALw_wcB',
    '_gcl_au': '1.1.1463966764.1667449732',
    '_ga': 'GA1.1.1196941600.1667449728',
    '_hjSessionUser_522327': 'eyJpZCI6IjA2ZGY2ZWI5LTU4YzItNTYwMS04NDM5LTMwNzQ5ZjE4YzFlNiIsImNyZWF0ZWQiOjE2Njc0NDk3MzI1MTAsImV4aXN0aW5nIjpmYWxzZX0=',
    '_hjFirstSeen': '1',
    '_hjIncludedInSessionSample': '0',
    '_hjSession_522327': 'eyJpZCI6IjM1MDk4NTcwLWMxZTEtNGRhMS1iN2E2LWI5NjYyMDQxMzY4ZCIsImNyZWF0ZWQiOjE2Njc0NDk3MzMzNjUsImluU2FtcGxlIjpmYWxzZX0=',
    '_hjAbsoluteSessionInProgress':'0',
    'cto_bundle': 'ZMyxy19UVXJRNmx3Q3ZOVkF6cG1UcGZyVyUyQllDelR3UU1EdWdna3lzcUhkbzRqcUdxSWlYVkVHb3BnRTBnOTIlMkZNSTBVNTRNRSUyRjFHWmZmMFc0b0YyS0Z3N2YlMkJmZzdkenBFNDlnQWhrblJmUU1ValVlMnU5TXA5RWt1SzVXOHJrJTJGJTJGdk9iMQ',
    '__utm': 'source%3Dgoogle%7Cmedium%3Dcpc%7Ccampaign%3DSEA_NBR_GGL_TXT_SBR_ALL_VN_ALL_UNK_UNK_C.ALL_X.9805780973_Y.99446805025_Q.e_K.Tiki_W.DT_R.430254349628_T.aud-892837214299%253Akwd-10246492_L.HP_O.CIR',
    '__iid': '749',
    '__su': '0',
    'amp_99d374': 'NSCzTDKNmHW_Dt0z89Tgm-...1ggtrvaeu.1ggts0c3d.9.d.m',
    '_ga_GSD4ETCY1D': 'GS1.1.1667449732.1.1.1667449778.14.0.0'
}'''

headers = {
    'User-Agent': 'ozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/107.0.0.0 Safari/537.36 Edg/107.0.1418.26',
    'Accept': 'application/json, text/plain, */*',
    'Accept-Language': 'en-US,en;q=0.9',
    'Referer': 'https://tiki.vn/dien-thoai-may-tinh-bang/c1789',
    'x-guest-token': 'Hkj5dnVZgsBb2r9SDhAGxpowKW0YQXeN',
    'Connection': 'keep-alive',
    'TE': 'Trailers',
}

params = {
    'limit': '40',
    'include': 'advertisement',
    'aggregations': '2',
    'trackity_id': '7efb4338-41ed-96b9-f796-785783de9f4c',
    'category': '1789',
    'page': '1',
    'src': 'c1789',
    'urlKey':  'dien-thoai-may-tinh-bang',
}

product_id = []
for i in range(1, 11):
    params['page'] = i
    response = requests.get('https://tiki.vn/api/personalish/v1/blocks/listings', headers=headers, params=params)#, cookies=cookies)
    if response.status_code == 200:
        print('request success!!!')
        for record in response.json().get('data'):
            product_id.append({'id': record.get('id')})
    time.sleep(random.randrange(3, 10))

df = pandas.DataFrame(product_id)
df.to_csv('product_id_ncds.csv', index=False)