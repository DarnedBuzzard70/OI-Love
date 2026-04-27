import requests
from bs4 import BeautifulSoup
def main():
    zhangyucheng_zuishuai()
def zhangyucheng_zuishuai():
    url = "https://www.weather.com.cn/weather/101281301.shtml"
    headers = {
        "User-Agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/120.0.0.0 Safari/537.36"
    }
    try:
        response = requests.get(url, headers=headers, timeout=10)
        response.encoding = "utf-8"
        if response.status_code != 200:
            print(f"请求失败，状态码：{response.status_code}")
            return
        soup = BeautifulSoup(response.text, "html.parser")
        weather_7d = soup.find("div", id="7d")
        if not weather_7d:
            print("未找到7天天气数据")
            return
        day_list = weather_7d.find_all("li")
        print("===== 桂林未来7天天气预报 =====")
        for day in day_list:
            if day.find("h1"):
                date = day.find("h1").get_text(strip=True)
            if day.find("p", class_="wea"):
                weather = day.find("p", class_="wea").get_text(strip=True)
            if day.find("p", class_="tem"):
                temp = day.find("p", class_="tem").get_text(strip=True)
            if day.find("p", class_="win"):
                wind = day.find("p", class_="win").get_text(strip=True)
            print(f"【{date}】")
            print(f"天气：{weather}")
            print(f"温度：{temp}")
            print(f"风力：{wind}")
            print("-" * 30)
    except Exception as e:
        print(f"爬取出错：{e}")
if __name__ == "__main__":
    main()