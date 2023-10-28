from selenium import webdriver
from selenium.webdriver.common.by import By
from selenium.webdriver.support.ui import WebDriverWait
import time

#
#C:\\Users\\ThanhDuy\\AppData\\Local\\Google\\Chrome\\User Data
# mở profile đã có sẵn
def initDriver():
	option = webdriver.EdgeOptions()
	option.add_argument("--user-data-dir=C:\\Users\\ThanhDuy\\AppData\\Local\\Microsoft\\Edge\\User Data")
	option.add_argument("--profile-directory=Default")
	driver = webdriver.ChromiumEdge(executable_path="D:\\Projects\\ChromeSelenium\\msedgedriver.exe", options=option)
	return driver

def ham_surf_face():
	driver = initDriver()
	driver.get('https://www.facebook.com/tienganhnghenoi/posts/pfbid0pLtpMTDFaszWMAthRuGnwaMaW6UsDHDmoTThrN9tXi74qwVR2SumGHuuu4nKp68Ul') #da co nick fb login san roi
	#wait khi story xuat hien <=> load success
	# WebDriverWait(driver, 10).until(lambda x: x.find_element(By.CLASS_NAME, "_6j_c"))
	time.sleep(2)
	count_eles_btn_reply = 0
	

	while(True):
		#scroll down
		driver.execute_script("window.scrollBy(0,0.7*window.innerHeight)")
		time.sleep(2)

		# eles_btn_like=driver.find_elements_by_css_selector('div[data-testid="UFI2ReactionLink/actionLink"] a') #selector cua nut like

		# class_name của element số lượng comment
		num_of_cmt_classname = 'x193iq5w xeuugli x13faqbe x1vvkbs x1xmvt09 x1lliihq x1s928wv xhkezso x1gmr53x x1cpjm7i x1fgarty x1943h6x xudqn12 x3x7a5m x6prxxf xvq8zen xo1l8bm xi81zsa'

		eles_btn_num_of_cmt = driver.find_elements(By.CLASS_NAME, num_of_cmt_classname)
      
		print(eles_btn_num_of_cmt)

		# for i in range(count_eles_btn_cmt):
		# 	eles_btn_reply[i].click()
		# 	eles_btn_cmt[i].send_keys("abc xsdf")
		# 	driver.find_element(By.NAME, 'submit').click()
		# 	time.sleep(3)
		


ham_surf_face()
