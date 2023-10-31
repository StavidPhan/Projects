import pandas
import requests

# cookies = {
#     '_trackity': '7efb4338-41ed-96b9-f796-785783de9f4c',
#     'TOKENS': '{%22access_token%22:%22Hkj5dnVZgsBb2r9SDhAGxpowKW0YQXeN%22%2C%22expires_in%22:157680000%2C%22expires_at%22:1825129724334%2C%22guest_token%22:%22Hkj5dnVZgsBb2r9SDhAGxpowKW0YQXeN%22}',
#     '_gac_UA-15036050-1': '1.1667449728.Cj0KCQjwqoibBhDUARIsAH2OpWhfKJYwjKaGPcEiUsbB-c-zVZbDPbY0DuIptDFq4e7sOVbxhYzBro0aAo4vEALw_wcB',
#     'delivery_zone': 'Vk4wMzQwMjQwMTM=',
#     'tiki_client_id': '1196941600.1667449728',
#     '_gcl_aw': 'GCL.1667449732.Cj0KCQjwqoibBhDUARIsAH2OpWhfKJYwjKaGPcEiUsbB-c-zVZbDPbY0DuIptDFq4e7sOVbxhYzBro0aAo4vEALw_wcB',
#     '_gcl_au': '1.1.1463966764.1667449732',
#     '__utm': 'source%3Dgoogle%7Cmedium%3Dcpc%7Ccampaign%3DSEA_NBR_GGL_TXT_SBR_ALL_VN_ALL_UNK_UNK_C.ALL_X.9805780973_Y.99446805025_Q.e_K.Tiki_W.DT_R.430254349628_T.aud-892837214299%253Akwd-10246492_L.HP_O.CIR',
#     '__iid': '749',
#     '__su': '0',
#     '_hjSessionUser_522327': 'eyJpZCI6IjA2ZGY2ZWI5LTU4YzItNTYwMS04NDM5LTMwNzQ5ZjE4YzFlNiIsImNyZWF0ZWQiOjE2Njc0NDk3MzI1MTAsImV4aXN0aW5nIjp0cnVlfQ==',
#     '_gid': 'GA1.2.822243885.1667652513',
#     'amp_99d374': 'NSCzTDKNmHW_Dt0z89Tgm-...1gh43rb87.1gh43rdju.h.q.1b; _gat=1',
#     '_ga': 'GA1.1.1196941600.1667449728',
#     '_hjIncludedInSessionSample': '0',
#     '_hjSession_522327': 'eyJpZCI6IjBkMGJlZmNiLTNmNGEtNDJlNS04MWU4LWNlMmRhODllMmZmZSIsImNyZWF0ZWQiOjE2Njc2NTkzMTY3NjIsImluU2FtcGxlIjpmYWxzZX0=',
#     '_hjAbsoluteSessionInProgress': '0',
#     'cto_bundle': 'A2jUBV9YSHc0bTJaRHVaQWdQU3Q4TjdZczRiOWRmdkRkZk1yaUlldk9IOTRFVGhCaXFHTGIyNmglMkZMQ1hKZXZiNUd5b01RSnBnU1Q3SSUyQkdJeVA4dzJLOHlEVnJkcWUlMkZUZzkyUGxONlIlMkJQSzhUc2hLSUhhenAyTUN6SHZnbWpLclphVlNx',
#     '_ga_GSD4ETCY1D': 'GS1.1.1667659316.4.0.1667659323.53.0.0'
# }

headers = {
    'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/107.0.0.0 Safari/537.36 Edg/107.0.1418.35',
    'Accept': 'application/json, text/plain, */*',
    'Accept-Language': 'en-US,en;q=0.9',
    'Referer': 'https://tiki.vn/dien-thoai-samsung-galaxy-a03s-4gb-64gb-hang-chinh-hang-p120450353.html?itm_campaign=CTP_YPD_TKA_PLA_UNK_ALL_UNK_UNK_UNK_UNK_X.119346_Y.1271190_Z.2854033_CN.Product-Ads-Manual&itm_medium=CPC&itm_source=tiki-ads&spid=126022664',
    'x-guest-token': 'Hkj5dnVZgsBb2r9SDhAGxpowKW0YQXeN',
    'Connection': 'keep-alive',
    'TE': 'Trailers',
}

params = (
    ('platform', 'web'),
    ('spid', 126022664)
)

def parser_product(json):
    d = dict()
    d['product_name'] = json.get('name')
    d['id'] = json.get('id')
    d['current_price'] = json.get('price')
    d['original_price'] = json.get('original_price')
    d['discount'] = json.get('discount')
    d['discount_rate'] = json.get('discount_rate')
    d['short_description'] = json.get('short_description') 
    d['rating_average'] = json.get('rating_average')  
    d['inventory_status'] = json.get('inventory_status')
    d['brand_name'] = json.get('brand').get('name')
    d['product_link'] = json.get('short_url')
    return d


df_id = pandas.read_csv('product_id_ncds.csv')
p_ids = df_id.id.to_list()
print(p_ids)
result = []
for pid in p_ids:
    response = requests.get('https://tiki.vn/api/v2/products/{}'.format(pid), headers=headers, params=params)#, cookies=cookies)
    # response.encoding = 'utf-8'
    if response.status_code == 200:
        print('Crawl data {} success !!!'.format(pid))
        result.append(parser_product(response.json()))

df_product = pandas.DataFrame(result)
print(df_product)
df_product.to_csv('crawled_data_ncds.csv', index=False, encoding='utf-8-sig')