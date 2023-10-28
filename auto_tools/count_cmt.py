import time

from selenium import webdriver
from selenium.webdriver.common.by import By
from selenium.webdriver.edge.service import Service

from webdriver_manager.microsoft import EdgeChromiumDriverManager


driver = webdriver.Edge(service=Service(EdgeChromiumDriverManager().install()))
driver.get("https://www.facebook.com/tienganhnghenoi/posts/pfbid0pLtpMTDFaszWMAthRuGnwaMaW6UsDHDmoTThrN9tXi74qwVR2SumGHuuu4nKp68Ul")

time.sleep(10)

search_field = driver.find_element(By.ID, ':r85:')

print(search_field)

driver.close()


