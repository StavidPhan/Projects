import requests
from bs4 import BeautifulSoup

# URL của trang web bạn muốn trích xuất thông tin từ
url = "https://www.facebook.com/tienganhnghenoi/posts/pfbid0pLtpMTDFaszWMAthRuGnwaMaW6UsDHDmoTThrN9tXi74qwVR2SumGHuuu4nKp68Ul"

# Sử dụng thư viện requests để tải nội dung của trang web
response = requests.get(url)

# Kiểm tra nếu yêu cầu tải trang thành công
if response.status_code == 200:
    # Sử dụng BeautifulSoup để phân tích nội dung HTML
    soup = BeautifulSoup(response.text, "html.parser")
    
    # Tìm thẻ có ID là "r85"
    element = soup.find(id="u_0_7y_Vs")
     
    # Kiểm tra xem thẻ có tồn tại không
    if element:
        # In nội dung của thẻ
        print(element.text)
    else:
        print("Không tìm thấy thẻ có ID là 'r85' trên trang web.")
else:
    print("Không thể tải trang web. Mã lỗi:", response.status_code)
