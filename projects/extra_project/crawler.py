import requests
from  bs4 import BeautifulSoup
url_main = "https://wiki.ubuntu.com/RandomPage"
response = requests.get(url_main)
soup = BeautifulSoup(response.text,'html.parser')
list_sub = soup.find_all('a')[11:-2]
list_url = []
for i in range(len(list_sub)):
    href = list_sub[i].get('href')
    url = url_main+href
    list_url.append(url)
for url in list_url:
    response = requests.get(url)
    soup = BeautifulSoup(response.text, 'html.parser')
    all_text = soup.get_text()
    ascii_text = ''.join(char for char in all_text if ord(char) < 128)
    with open('E:/test/ascii_text.txt', 'a+', encoding='utf-8') as file:
         file.write(ascii_text)
