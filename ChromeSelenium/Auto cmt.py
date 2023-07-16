from selenium import webdriver
from selenium.webdriver.common.by import By
from selenium.webdriver.support.ui import WebDriverWait
import time

#
#C:\\Users\\ThanhDuy\\AppData\\Local\\Google\\Chrome\\User Data
# mở profile đã có sẵn
def initDriver():
	option = webdriver.ChromeOptions()
	option.add_argument("--user-data-dir=C:\\Users\\ThanhDuy\\AppData\\Local\\Google\\Chrome\\User Data")
	option.add_argument("--profile-directory=Default")
	driver = webdriver.Chrome(executable_path='D:\\Projects\\Chrome Selenium\\chromedriver.exe', options=option)
	return driver

def ham_surf_face():
	driver = initDriver()
	driver.get('https://m.facebook.com/groups/172855739977091/posts/1168098560452799/') #da co nick fb login san roi
	#wait khi story xuat hien <=> load success
	WebDriverWait(driver, 10).until(lambda x: x.find_element(By.CLASS_NAME, "_6j_c"))
	time.sleep(2)
	count_eles_btn_reply = 0
	

	while(True):
		#scroll down
		driver.execute_script("window.scrollBy(0,0.7*window.innerHeight)")
		time.sleep(2)

		# eles_btn_like=driver.find_elements_by_css_selector('div[data-testid="UFI2ReactionLink/actionLink"] a') #selector cua nut like

		eles_btn_reply = driver.find_elements(By.CLASS_NAME, '_2b0a')
		eles_btn_cmt = driver.find_elements(By.CLASS_NAME, '_uwx mentions-input')

		count_eles_btn_reply = len(eles_btn_reply)
		count_eles_btn_cmt = len(eles_btn_cmt)

		for i in range(count_eles_btn_cmt):
			eles_btn_reply[i].click()
			eles_btn_cmt[i].send_keys("abc xsdf")
			driver.find_element(By.NAME, 'submit').click()
			time.sleep(3)

		
		#print(count_eles_btn_reply)


ham_surf_face()
